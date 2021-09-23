#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "kseq.h"
#include "kann_data.h"

KSTREAM_INIT(int, dataread, 16384)

int dataread(int unused, char *buf, int bufsize)
{
    int ret;
    ocall_read_datafile(&ret, buf, 1, bufsize, bufsize); 
    
    return ret;
}

kann_data_t *kann_data_read(const char *fn, int max_sample_cnt)
{
	kstream_t *ks;
	kann_data_t *d;
	int m_row = 0, dret, m_grp = 0, grp_size = 0;
	kstring_t str = {0,0,0};

    int ret = 0;
	open_datafile(&ret, fn); // ret should be 0; 1 means failed.
	
	int fp = 1234;

	ks = ks_init(fp);

	d = (kann_data_t*)calloc(1, sizeof(kann_data_t));
	while (ks_getuntil(ks, KS_SEP_LINE, &str, &dret) >= 0) {
		int st, k;
		size_t i;
		if (str.s[0] == '#') {
			for (i = 0, k = 0; i < str.l; ++i)
				if (str.s[i] == '\t') ++k;
			if (k > 0) {
				d->n_col = k;
				d->cname = (char**)malloc(d->n_col * sizeof(char*));
				for (i = 0, k = st = 0; i <= str.l; ++i) {
					if (i == str.l || str.s[i] == '\t') {
						if (k > 0) str.s[i] = 0, d->cname[k-1] = strdup(&str.s[st]);
						++k, st = i + 1;
					}
				}
			}
			continue;
		}
		if (str.s[0] == 0) {
			if (d->n_grp == m_grp) {
				m_grp = m_grp? m_grp<<1 : 8;
				d->grp = (int*)realloc(d->grp, m_grp * sizeof(int));
			}
			d->grp[d->n_grp++] = grp_size;
			grp_size = 0;
			continue;
		}
		for (i = 0, k = 0; i < str.l; ++i)
			if (str.s[i] == '\t') ++k;
		if (d->n_col == 0) d->n_col = k;
		if (k != d->n_col) continue; // TODO: throw a warning/error
		if (d->n_row == m_row) {
			m_row = m_row? m_row<<1 : 8;
			d->x = (float**)realloc(d->x, m_row * sizeof(float*));
			d->rname = (char**)realloc(d->rname, m_row * sizeof(char*));
		}
		d->x[d->n_row] = (float*)malloc(d->n_col * sizeof(float));
		for (i = 0, k = st = 0; i <= str.l; ++i) {
			if (i == str.l || str.s[i] == '\t') {
				char *p;
				if (k == 0) {
					str.s[i] = 0;
					d->rname[d->n_row] = strdup(&str.s[st]);
				} else d->x[d->n_row][k-1] = strtod(&str.s[st], &p);
				++k, st = i + 1;
			}
		}
		++d->n_row, ++grp_size;
		
		if(max_sample_cnt != 0)
		    if(d->n_row >= max_sample_cnt) break;
	}
	if (d->n_grp == m_grp) {
		m_grp = m_grp? m_grp<<1 : 8;
		d->grp = (int*)realloc(d->grp, m_grp * sizeof(int));
	}
	d->grp[d->n_grp++] = grp_size;
	free(str.s);
	ks_destroy(ks);

	d->x = (float**)realloc(d->x, d->n_row * sizeof(float*));
	d->rname = (char**)realloc(d->rname, d->n_row * sizeof(char*));
	d->grp = (int*)realloc(d->grp, d->n_grp * sizeof(int));

    close_datafile();
	return d;
}

void kann_data_free(kann_data_t *d)
{
	int i;
	if (d == 0) return;
	for (i = 0; i < d->n_row; ++i) {
		if (d->rname) free(d->rname[i]);
		free(d->x[i]);
	}
	if (d->cname) for (i = 0; i < d->n_col; ++i) free(d->cname[i]);
	free(d->x); free(d->cname); free(d->rname); free(d->grp); free(d);
}

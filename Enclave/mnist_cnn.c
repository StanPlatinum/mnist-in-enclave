#include <stdlib.h>
#include <assert.h>
#include "kann_extra/kann_data.h"
#include "kann.h"

kann_t *ann;

int initialize()
{
	char *fn_in = 0, *fn_out = 0;
	int c, mini_size = 64, max_epoch = 20, max_drop_streak = 10, n_h_fc = 128, n_h_flt = 32, n_threads = 1;
	float lr = 0.001f, dropout = 0.2f, frac_val = 0.1f;

	kad_trap_fe();		
	int ret = 0;
	
	kprintf("trying to open model file...\n");
	open_networkfile(&ret, "mnist_model_data/mnist-cnn.kan"); // ret should be 0; 1 means failed.
	
	if(ret != 0) 
	{
	    kprintf("open network failed.\n");
	    return -1;
    }else
        kprintf("open network succeeded.\n");
    
	ann = kann_load_fp();
	
	if(ann == NULL) 
	{
	    kprintf("load network failed.\n");
	    return -1;
    }else
        kprintf("load network succeeded.\n");
        
    close_networkfile();
}

int mnist_cnn()
{   
	kann_data_t *x;
      
	x = kann_data_read("mnist_model_data/mnist-test-x.knd", 50);
	
	//
	assert(x->n_col == 28 * 28);
    float res = 0.0;
	{ // applying
		int i, j, n_out; 
		kann_switch(ann, 0);
		n_out = kann_dim_out(ann);
		assert(n_out == 10);
		//for (i = 0; i < x->n_row; ++i) {
		for (i = 0; i < 50; ++i) {
			float *y = NULL;
			y = kann_apply1(ann, x->x[i]);
			
	    //	kprintf("%f\n", *y);
			if(y != NULL) 
			{	    
//			    if (x->rname) kprintf("%s\t", x->rname[i]);
			    for (j = 0; j < n_out; ++j) {
				    if(y[j] > 0.5) 
				    {
				        kprintf("class %d\n", j);
				        break;
				    }
			    }
//			    memset(y, 0, sizeof(float));
//			    free(y);
			    
			}
			else
			    kprintf("NULL returned.\n");
			
			
//			memset(&y[j], 0, sizeof(float));
		}
	}
		
	kann_data_free(x);
	
	//clear(ann);

	//for (int i = 0; i < 4; ++i) {
	    
   // }
	
    kprintf("close model file...\n");
	return 0;
}

void destroy()
{
    kann_delete(ann);
}

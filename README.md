## Disclaimer Notice

This proj is not ready for use.

### usage

```
source /opt/intel/clang_sgx_sdk/sgxsdk/environment
make
./app 
```

or run ``./app | mnist_model_data/mnist-eval.pl``.


Model and test data are not uploaded due to space limitaiton of github.


### note
please check the gcc version used, and copy the corresponding header files. For example, I am using GCC 5.4.0, then 
```
cp /usr/lib/gcc/x86_64-linux-gnu/5/include/* Enclave/msse/
```


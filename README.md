# VS2015_update3_optimizer_bug
Sample program to demonstrate a bug in VS2015 update 3 SSA optimizer

Works fine in all configurations except Release|x64

Compile attached project in Release|x64 and observe the bug. Turning off SSA optimizer with command line option "-d2SSAOptimizer-" or running it in Debug|x64 fixes the bug.

The original discussion of this bug: https://github.com/kimwalisch/primesieve/issues/20

This bug breaks primesieve with VS2015 update 3

Update: it seems the computation is correct, but the result is not saved anywhere, and printf prints garbage.

	printf("threadStop = %llu (expected 11001)\r\n", threadStop);
000000013FCE108C  mov         rdx,rdi  
000000013FCE108F  lea         rcx,[string "threadStop = %llu (expected 11001"... (013FCE2228h)]  
000000013FCE1096  call        printf (013FCE1130h)  
	threadStop = align(threadStop); // !!! The bug is here !!!
000000013FCE109B  cmp         rdi,qword ptr [rbx]  
000000013FCE109E  je          ParallelPrimeSieve::sieveInternal+69h (013FCE10C9h)  
000000013FCE10A0  mov         rax,8888888888888889h  
000000013FCE10AA  mul         rax,rdi  
000000013FCE10AD  shr         rdx,4  
000000013FCE10B1  imul        rax,rdx,1Eh  
000000013FCE10B5  add         rax,20h  
000000013FCE10B9  lea         rcx,[rbx+8]  
000000013FCE10BD  lea         rbx,[rsp+28h]  
000000013FCE10C2  cmp         qword ptr [rcx],rax  
000000013FCE10C5  cmovb       rbx,rcx  
000000013FCE10C9  mov         rbx,qword ptr [rbx]  
	printf("threadStop = %llu (expected 11012)\r\n\r\n", threadStop);
000000013FCE10CC  mov         rdx,rbx  
000000013FCE10CF  lea         rcx,[string "threadStop = %llu (expected 11012"... (013FCE2250h)]  
000000013FCE10D6  call        printf (013FCE1130h)  

"rax" has correct value 11012 here but it's not passed to printf at all.

It looks like that instead of "cmovb rbx,rcx / mov rbx,qword ptr [rbx]" compiler should generate "cmovb rax, qword ptr [rcx] / mov rbx,rax" or something similar.

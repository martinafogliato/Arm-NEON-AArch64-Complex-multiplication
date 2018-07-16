
short conjugate75[8]__attribute__((aligned(16))) = {-1,1,-1,1,-1,1,-1,1} ;

  int16x8_t *vector1,*vector2;
  int16x4x2_t trn0, trn1;
  int32x4_t tmp0,tmp1;
  int16x4_t tmpccgg0, tmpddhh0, tmpbafe0, tmpccgg1, tmpddhh1, tmpbafe1;
 
for (#iterations) {
    
	tmpddhh0 = ((int16x4_t*)vector2)[0]; //c d g h
    tmpccgg0 = ((int16x4_t*)vector2)[0]; //c d g h
    trn0 = vtrn_s16(tmpccgg0, tmpddhh0); //c c g g mmtrn[0]    d d h h mmtrn[1]
    tmpddhh0 = vmul_s16(((int16x4_t*)&trn0)[1], *(int16x4_t*)conjugate75); //-d d -h h
    tmpbafe0 = vrev32_s16(((int16x4_t*)vector1)[0]); //b a f e
    tmp0 = vmull_s16(((int16x4_t*)vector1)[0], ((int16x4_t*)&trn0)[0]); //ac bc eg fg
    tmp0= vmlsl_s16(mmtmp0, tmpddhh0, tmpbafe0); //ac+bd bc-ad eg+fh fg-eh

    tmpddhh1 = ((int16x4_t*)vector2)[1];
    tmpccgg1 = ((int16x4_t*)vector2)[1];
    trn1 = vtrn_s16(tmpccgg1, tmpddhh1);
    tmpddhh1 = vmul_s16(((int16x4_t*)&trn1)[1], *(int16x4_t*)conjugate75);
    tmpbafe1 = vrev32_s16(((int16x4_t*)vector1)[1]) ;
    tmp1 = vmull_s16(((int16x4_t*)vector1)[1], ((int16x4_t*)&trn1)[0]);
    tmp1 = vmlsl_s16(mmtmp1, tmpddhh1, tmpbafe1);

    vector1[0] = vcombine_s16(vshrn_n_s32(tmp0, 15), vshrn_n_s32(tmp1, 15));
   
	vector1++;
    vector2++;
 }


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//			�A���e�i�`��w�b�_�[�@�@antenna.h
//				�_�C�|�[���A���e�i
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//				�v�Z
//////////////////////////////////////////////////////////////////////////////////
void Calculation(void)
{
	//========================================================
	//			���[�J���ϐ�
	//========================================================
	//--�J�E���^
	int i,j,k,m,n;

	//--�v�Z�Ŏg�p����ϐ�
	double rrx , rry , rrz;				//�Z�O�����g�n�_
	double drx , dry , drz;				//�Z�O�����g�I�_
	double ssx , ssy , ssz;				//�Z�O�����g�̒P�ʃx�N�g��
	double dcl;							//�Z�O�����g����

	//--�G�������g���֌W�i���C���[�{���j
	int n_array;						//�_�C�|�[���̖{��

	//--�e�����̕�����
	int nbun_pole1,nbun_pole2,nbun_pole3,nbun_pole4;						//�_�C�|�[���̕�����
	
	//--�e���̃Z�O�����g��
	int n_pole;							//�_�C�|�[���̃Z�O�����g��

	//--�݌v�l�֌W
	double r_pole1,r_pole2,r_pole3;						//�_�C�|�[���̒���
	double wire_radius;					//���C���[���a

	//========================================================
	//			���ˊE�v�Z�ݒ�		�P�ʁF(deg)
	//========================================================
	//--�v�Z���[�h
	AXMODE = 0;			//(0=�ӌŒ�, 1=�ƌŒ�)

	//--�ώ�
	DegDelta =  0.1;	//���ݕ�("0.0"�֎~)
	DegStart =  -15.0;	//�����p
	DegWidth =  30.0;	//�͈�

	//--�Œ莲
	FixAngle =  0.0;	//�Œ�p�x

	//========================================================
	//			�݌v���g��		FREQ0	(f0)	�P�ʁF(Hz)
	//			���d���g��		USEF	(f)		�P�ʁF(Hz)
	//========================================================
	//--�݌v���g���ݒ�
	for(k=0;k<1;k++){

		for(m=0;m<1;m++){//�ۓ��f�q
			
			for(n=-0;n<1;n++){//���g��

	FREQ0 = 3.0 * pow(10.0,9.0);

	//--�d�������ݒ�@
	USEF  = FREQ0 * (1.00+(0.001*n));				//f���Ƃ�ɂ͌W����ύX

	//--�݌v���g���̎��R��Ԕg��
	RAMDA0= C/FREQ0;

	//========================================================
	//			�S���C���[��	NWIR
	//			�Z�O�����g��	NSEG
	//			���d�_��		NFED
	//			�S�d���v�Z�_��	NSEG0
	//			�y���א�		NLOAD		
	//========================================================
	//--�S���C���[���ݒ�
	n_array = 7;
	NWIR = n_array;

	//--����������
	nbun_pole1 = 42;//�~(0~315)
	nbun_pole2 = 6;//�~(315~360)
	nbun_pole3 = 6;//�ۓ��f�q
	nbun_pole4 = 12;//���d�_//�_�C�|�[���̕�����

	//--�S�Z�O�����g���ݒ�
	n_pole = 2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1) + (nbun_pole4+1+1);
	NSEG = n_pole;						//�S�Z�O�����g��

	//--�S�d���v�Z�_��  [NSEG0=NSEG-NWIR]	�������������폜�@�s��
	NSEG0 = NSEG - NWIR;

	//--���d�_��
	NFED = 1;

	//--�C���s�[�_���X���א�
	NLOAD = 0;

	//========================================================
	//			�z��m�ۂƏ�����
	//			[���ˊE�v�Z�ݒ�,NWIR,NSEG,NFED,NLOAD]
	//				�ݒ��Ɋ֐��Ăяo��
	//			�������������폜�@�s��
	//========================================================
	MakeMatAll();								//�z��m��(���R�����g�A�E�g�֎~��)
	Initialization();							//�z��ƌv�Z�p�ϐ��̏�����

	//========================================================
	//			�`��l��`
	//			������RAMDA0����@�W���Œl��`(������)
	//========================================================
	//--����
	r_pole1 = (0.933+0.001*k) * RAMDA0;//�~C
	r_pole2 = (0.136+0.001*m) * RAMDA0;//�ۓ��f�q��l
	r_pole3 = (0.125 * RAMDA0) * 2.0;//����h


	//--���C���[���a
	wire_radius = RAMDA0/200;

	//========================================================
	//			�o�̓t�@�C���p�̃p�����[�^
	//			PARA1 �� PARA2 �ɒl����͂���D
	//========================================================
	PARA1 = r_pole1/RAMDA0;//�o�͗p�p�����[�^�@
	PARA2 = r_pole2/RAMDA0;//�o�͗p�p�����[�^�A
	PARA3 = USEF/FREQ0;

	//========================================================
	//			�݌v�l����		�P�ʁF(m)
	//			�Z�O�����g�n�_	RX[ ] , RY[ ] , RZ[ ] 
	//			�P�ʃx�N�g��	SX[ ] , SY[ ] , SZ[ ]
	//			�Z�O�����g��	SEGL[ ]
	//========================================================
	
	double M_PI=3.14159265358979323846264338327950288;
	double han,t;

	han = r_pole1/(2.0*M_PI);//���a
	t = 360/48;//�~�̃Z�O�����g���̊p�x(����͉~�S�̂̕�����)

//------------------------------------------------�@�~(0~315)---------------------------------------------------------
	for(j = 0; j < nbun_pole1+1; ++j){
		i=j;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j-1));										//�n�_�ʒu�v�Zx
		rry = han * sin((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j-1));										//�n�_�ʒu�v�Zy
		rrz = r_pole3 * 0.5;	//�n�_�ʒu�v�Zz
		drx = han * cos((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//�I�_�ʒu�v�Zx
		dry = han * sin((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//�I�_�ʒu�v�Zy
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}



//------------------------------------------------�A�~(315~360)---------------------------------------------------------
	for(j = 0; j < nbun_pole2+1; ++j){
		i=j+nbun_pole1+1;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j-1));											//�n�_�ʒu�v�Zx
		rry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j-1));											//�n�_�ʒu�v�Zy
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//�I�_�ʒu�v�Zx
		dry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zy
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}


//------------------------------------------------�E�I�[�o�[���b�v:�ۓ��f�q------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		i = j+nbun_pole1+nbun_pole2+1+1;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//�n�_�ʒu�v�Zx
		rry = han * sin((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zx
		dry = han * sin((2.0*M_PI/360)*(-45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}


//------------------------------------------------�B�ۓ��f�q------------------------------------------------------------

	for(j = 0; j < nbun_pole3; ++j){
		i=j+nbun_pole1+nbun_pole2+1+1+1;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = (han - ((j+0) * (r_pole2/nbun_pole2)))*cos((M_PI/180)*(-45));										        //�n�_�ʒu�v�Zx
		rry = (han - ((j+0) * (r_pole2/nbun_pole2)))*sin((M_PI/180)*(-45)); 												//�n�_�ʒu�v�Zy
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = (han - ((j+1) * (r_pole2/nbun_pole2)))*cos((M_PI/180)*(-45)); 												//�I�_�ʒu�v�Zx
		dry = (han - ((j+1) * (r_pole2/nbun_pole2)))*sin((M_PI/180)*(-45));												//�I�_�ʒu�v�Zy
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}

/*
//------------------------------------------------�D�I�[�o�[���b�v:�~(0~315)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		i = j+nbun_pole1+nbun_pole2+nbun_pole3;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((M_PI/180) * t * (j-11));												//�n�_�ʒu�v�Zx
		rry = han * sin((M_PI/180) * t * (j-11));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((M_PI/180) * t * ((j-1)-11));												//�I�_�ʒu�v�Zx
		dry = han * sin((M_PI/180) * t * ((j-1)-11));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}
*/
/*
//------------------------------------------------�F�I�[�o�[���b�v:�~(315~360)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		i = j+nbun_pole1+nbun_pole2+nbun_pole3+1+1;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((M_PI/180) * t * (j-13));												//�n�_�ʒu�v�Zx
		rry = han * sin((M_PI/180) * t * (j-13));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((M_PI/180) * t * ((j-1)-13));												//�I�_�ʒu�v�Zx
		dry = han * sin((M_PI/180) * t * ((j-1)-13));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
	}
*/
//------------------------------------------------�I���˔�------------------------------------------------------------

	for(j = 0; j<nbun_pole1+nbun_pole2+nbun_pole3+1+1+1; ++j){
		i =j+nbun_pole1+nbun_pole2+nbun_pole3+1+1+1;
		//--�v�Z���ʑ��
		RX[i] = RX[j];											//�n�_�ʒux
		RY[i] = RY[j];											//�n�_�ʒuy
		RZ[i] = (-1.0)*RZ[j];									//�n�_�ʒuz
		SX[i] = SX[j];											//�P�ʃx�N�g��x
		SY[i] = SY[j];											//�P�ʃx�N�g��y
		SZ[i] = (-1.0)*SZ[j];									//�P�ʃx�N�g��z
		SEGL[i] = SEGL[j];										//�Z�O�����g��
	}

//------------------------------------------------�G�I�[�o�[���b�v:���d�_(-z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		i = j+2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1);

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//�n�_�ʒu�v�Zx
		rry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//�n�_�ʒu�v�Zy ���a
		rrz = (-1.0) * r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zx
		dry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zy ���a
		drz = (-1.0) * r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
	}

//------------------------------------------------�C���d�_------------------------------------------------------------

	for(j = 0; j < nbun_pole4; ++j){
		i = j+2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1)+1;

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = 0.0;												//�n�_�ʒu�v�Zx
		rry = (-1.0)*han;											//�n�_�ʒu�v�Zy ���a
		rrz = (-1.0)*(r_pole3*0.5) + (j+0)*(r_pole3/nbun_pole4);		//�n�_�ʒu�v�Zz
		drx = 0.0;												//�I�_�ʒu�v�Zx
		dry = (-1.0)*han;												//�I�_�ʒu�v�Zy ���a
		drz = (-1.0)*(r_pole3*0.5) + (j+1)*(r_pole3/nbun_pole4);		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
	}
	

//------------------------------------------------�G�I�[�o�[���b�v:���d�_(+z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		i = j+2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1)+nbun_pole4+1;


		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//�n�_�ʒu�v�Zx
		rry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3 * 0.5;		//�n�_�ʒu�v�Zz
		drx = han * cos((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//�I�_�ʒu�v�Zx
		dry = han * sin((2.0*M_PI/360)*(-90) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3 * 0.5;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
	}






//--------------------------------------------------------------------------------------------------------------------
	//========================================================
	//			�e�Z�O�����g�̃��C���[���a����	�P�ʁF(m)
	//			RA[ ]		���C���[���a
	//========================================================
	for(i = 0; i < NSEG; ++i){
		RA[i] = wire_radius;	
	}

	//========================================================
	//			�e�G�������g(���C���[)���̃Z�O�����g��
	//			SEGN[ ]
	//========================================================
	
	//�@���@�I�[�o�[���b�v���݂Ł@��
	SEGN[0] = nbun_pole1 +1;
	SEGN[1] = nbun_pole2 +1;
	SEGN[2] = nbun_pole3 +1;
	SEGN[3] = nbun_pole1 +1;
	SEGN[4] = nbun_pole2 +1;
	SEGN[5] = nbun_pole3 +1;
	SEGN[6] = nbun_pole4 +2;
	
	//========================================================
	//			���d�֌W�ݒ�
	//			���d�ʒu		FEDP[ ]
	//			���d�d��		FEDV[ ]
	//
	//			���ʒu  FEDP[ ]
	//					[���d�������ʒu]-[���d���������C���[(���Ԗ�)]
	//			���d��  FEDV[ ]
	//				�@��P���d�̓d��
	//					�s���t���d��p����ꍇ   -2�~(1+j0)[V]
	//					���t���d��p����ꍇ     -1�~(1+j0)[V]
	//				�A���˔t���_�C�|�[����(���˔t�����t���d�A���e�i)
	//					��P���d(���˔\��)   -1�~(1+j0)[V]
	//					��Q���d(���˔���)    1�~(1+j0)[V]
	//						(���˔̕\�Ɨ��ŋ��d�ʑ����t�ɂ���)
	//				�B��P���d���C���[�W�@�̏ꍇ
	//					���̋��d�_���C���[�W�@��K�p����D
	//				�C��P���d���C���[�W�@��p���Ȃ��ꍇ
	//					���̋��d�_���C���[�W�@��p���Ȃ��D
	//				�D�������d�̓d���E�ʑ�������
	//					��P���d�͏����@�A��K�p
	//					��P���d�ȊO�Ő�����s���D
	//========================================================
	FEDP[0] = 114;				// [�A���e�i�̒���]-[1�{��]
	FEDV[0] = -2.0 * Complex( 1.0 , 0.0 );	// 1.0+j0.0[V]

	//========================================================
	//			�C���s�[�_���X���׊֌W�ݒ�
	//			���׈ʒu		LOADP[ ]
	//			���גl�@		LOADZ[ ]
	//
	//			���ʒu    LOADP[ ]
	//					[���ׂ������ʒu]-[���ׂ��������C���[(���Ԗ�)]
	//			�����גl�@LOADZ[ ]  (50����ڑ�����ꍇ)
	//				�@���˔ɒ�R��t����ꍇ		 -2�~(50+j0)[��]
	//				�A���C���̓r���ɒ�R��t����ꍇ -1�~(50+j0)[��]
	//				�B�ڑ��Ώۂɂ�炸�C�l�́u�}�C�i�X(-)�v�ɂȂ�
	//								(��R�l�̓x�N�g���ł͖�������)
	//========================================================


	//========================================================
	//			�e�Z�O�����g����̕��ˏ�Ԃ�ݒ�(�������ːݒ�)
	//			RAD_MODE[ ] = 1 or 0
	//				(0 : ���˃J�b�g   1 : �ʏ�̕���)
	//			�������őS��RAD_MODE[ ]=1 �ɐݒ�ς�
	//========================================================


	//========================================================
	//			�d���E���ˊE�v�Z
	//========================================================	
	ConfCheck();				//�`�󌟍�
	MakeZmn();					//Zmn�쐬
	MakeCurrent();				//�d���v�Z
	MakePhase();				//�d���ʑ��v�Z
	Radiation();				//���ˊE�v�Z
	LapsedTime();				//�o�ߎ��Ԏ擾

	//========================================================
	//			�f�[�^�o��
	//========================================================	
	OutputConf();				//�`��o��
	OutputCurrent();			//�d���o��
	OutputRad();				//���ˊE�o��
	OutputChara();				//�����f�[�^�o��

	//========================================================
	//			�C�Ӄf�[�^�o��	free.dat
	//				�g�p�t�@�C���|�C���^ [fp_free]
	//========================================================	

	//-----------------------------------------------------------------------------------------------------------
/*	
	//	�~�Δg���� antenna_chara2
	//--�ő���˕����T��

	int n,maxang,zang;
	double gaimax;

	n = 0;
	maxang = 0;
	gaimax = RGAI[maxang];
	for(i = DegStart ;i <= DegStart+DegWidth ;i = i + DegDelta){
		if(RGAI[n]>=gaimax){
			gaimax = RGAI[n];
			maxang = n;
		}
		if(LGAI[n]>=gaimax){
			gaimax = LGAI[n];
			maxang = n;
		}
		n = n + 1;
	}

	//--Z�������T��(0�x�����T��)�ƌŒ�̏ꍇX�������T��
	n = 0;
	for(i = DegStart ;i <= DegStart+DegWidth ;i = i + DegDelta){
		if( (int)(i)==1.0){
			zang = n;
		}
		n = n + 1;
	}

	//--�����o��
	//    PARA1,PARA2
	//      �����o�͂ŏo�͂��Ă���PARA1,PARA2�͎��g�������Ȃǂ��v�Z�����ꍇ�ɕ\
	//      ��O���t�����₷�����邽�߂̃��m�v�Z���ł͉����g�p���Ă��Ȃ��̂ŁC
	//      �o�͂��Ȃ��Ă����Ȃ��ꍇ�͏����Ȃ�
	//    �\������
	//      �A���e�i�̌������s����ŁC�K�v�ȏ�̏����ȉ��̌������o�͂��Ă��Ȃ��D
	//      ����ȏ�̌������K�v�Ȃ�΁C�C�ӏo�͂�p����
	fprintf(fp_free," %13.6f %13.6f %13.6f **",PARA1,PARA2,PARA3);
	fprintf(fp_free," %9.2f %9.2f",Zin[0].re,Zin[0].im);
	fprintf(fp_free," %8.3f %8.3f **",VSWR_50[0],VSWR_75[0]);
	fprintf(fp_free," %8.3f",DegStart+DegDelta*maxang);
	fprintf(fp_free," %9.3f %9.3f",RGAI[maxang],LGAI[maxang]);
	fprintf(fp_free," %9.3f %7.3f **",RLGAI[maxang],AR[maxang]);
	fprintf(fp_free," %9.3f %9.3f",RGAI[zang],LGAI[zang]);
	fprintf(fp_free," %9.3f %7.3f\n",RLGAI[zang],AR[zang]);
	//---------------------------------------------------------------------------------------------------------------

	/*fprintf(fp_free," PARA1 = %9.5f    PARA2 = %9.5f\n",PARA1,PARA2);	//�p�����^�[
	fprintf(fp_free," Zin = %9.2f %9.2f\n",Zin[0].re,Zin[0].im);        //�C���s�[�_���X
	fprintf(fp_free," �v�Z���� = %d:%d\n",la_min,la_sec);				//�o�ߎ��ԕ\��
	fprintf(fp_free," \n\n\n");	
	//���s
*/
	//========================================================
	//			�z��̊J��
	//========================================================	
	DelMatAll();				//�z��J��(���R�����g�A�E�g�֎~��)
}

}
}
}
//============================================================================
//					�ϐ��Ɣz��ꗗ
//============================================================================
//
//--�`�� ���d
//		double	FREQ0					�݌v���g��f0
//		double	RAMDA0					�݌v���g���̎��R��Ԕg��
//		double	USEF					���d���g��
//		int		NWIR					�S���C���[��
//		int		NSEG					�S�Z�O�����g��
//		int		NFED					�S���d�_��
//		int		NSEG0					�S�d���v�Z�_��
//		int		NLOAD					��R�����א�
//--���ˊE�v�Z
//		int		AXMODE   				(0=�ӌŒ�, 1=�ƌŒ�)	
//		double	DegDelta 				���ݕ�
//		double	DegStart 				�����p
//		double	DegWidth 				�͈�
//		double	FixAngle 				�Œ莲�p�x
//--���ԑ���
//		int		la_min	la_sec			�� �b
//--�v�Z�񂵗p�p�����[�^
//		double	PARA1,PARA2				�p�����[�^�@�ƇA
//--�`��z��
//		double	RX[ ]  RY[ ]  RZ[ ]		�e�Z�O�����g�̎n�_
//		double�@SX[ ]  SY[ ]  SZ[ ]		�P�ʃx�N�g���̐���
//		double	SEGL[ ]	RA[ ]			�e�Z�O�����g�̒��� ���a�@		
//		int�@	SEGN[ ]					�e���C���[�̃Z�O�����g��
//		int		FEDP[ ]					�e���d�ʒu
//		complex	FEDV[ ]					�e���d�d��
//		int		RAD_MODE[ ]				�e�Z�O�����g�̕��˃��[�h
//		int		LOADP[ ]				�e�C���s�[�_���X���׈ʒu
//		complex LOADZ[ ]				�e�C���s�[�_���X���גl
//--�d���z��
//		complex Zmn[ ][ ]				�C���s�[�_���X�s��	
//		complex Im[ ]					�d�����z
//		double  PhaseIm[ ]				�d���̈ʑ�
//--���̓C���s�[�_���X
//		complex Zin[ ]					�e���d�_�̓��̓C���s�[�_���X
//		double  VSWR_50[ ]  VSWR_75[ ]	�e���d�_��50����75���ɑ΂���VSWR
//--���ˊE�z��
//		complex TRAD[ ] FRAD[ ]			E�Ƃ�E�ӂ̕��ˊE
//		complex RRAD[ ] LRAD[ ]			ER ��EL �̕��ˊE
//		double TPHASE[ ] FPHASE[ ]		E�Ƃ�E�ӂ̈ʑ�
//		double RPHASE[ ] LPHASE[ ]		ER ��EL �̈ʑ�
//		double TGAI[ ] FGAI[ ]			E�Ƃ�E�ӂ̗���
//		double TFGAI[ ]					E�Ƃ�E�ӂ̍��v�̗���
//		double RLGAI[ ]					ER ��EL �̍��v�̗���
//		double RGAI[ ] LGAI[ ]			ER ��EL �̗���
//		double TPAT[ ] FPAT[ ]			E�Ƃ�E�ӂ̃p�^�[��
//		double RPAT[ ] LPAT[ ]			ER ��EL �̃p�^�[��
//		double AR[ ]					����
//--��{�����萔
//		double PI						��
//		double C						����
//		double e0						�^�󒆂̓�������0
//		double u0						�^�󒆂̗U�d����0
//		double R						1.0 �Œ�
//--���ȗ��p
//		complex J						�����P�ʁ@J=��-1
//--�ϕ��p
//		int GaussTenNo					�K�E�X�ϕ����_  [ 4�Œ�]�i�ʏ�p�j
//		int GaussTenSpe					�K�E�X�ϕ����_��[40�Œ�]�i���ٓ_�p�j
//--�v�Z�p
//		double k0						k0
//		complex uair					u(air)
//		double Beta;					��
//============================================================================
//============================================================================

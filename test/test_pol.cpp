#include <gtest.h>
#include "Polinom.h"


TEST(monom, can_create_monom)
{
	ASSERT_NO_THROW(monom m);
}

TEST(monom, empty_monom)
{
	monom m;
	EXPECT_EQ(0, m.coeff);
	EXPECT_EQ(0, m.st);
	EXPECT_EQ(0, m.next);
}

TEST(Polinom, can_create_Polinom)
{
	ASSERT_NO_THROW(Polinom P);
}

TEST(Polinom, new_pol_is_empty)
{
	Polinom P;

	EXPECT_EQ(0, !P.empty());
}

TEST(Polinom, can_copy_Polinom)
{
	Polinom P;

	ASSERT_NO_THROW(Polinom Q=P);
}

TEST(Polinom, copyed_pol_is_empty)
{
	Polinom P;
	Polinom Q=P;

	EXPECT_EQ(0, !P.empty());
}

TEST(Polinom, can_Add_monom)
{
	Polinom P;

	ASSERT_NO_THROW(P.AddMonom(4,123));
}

TEST(Polinom, empty_pol_after_add_const)
{
	Polinom P;

	P.AddMonom(-1,0);
	P.AddMonom(1,0);

	EXPECT_EQ(0, !P.empty());
}


TEST(Polinom, can_assign)
{
	Polinom P,Q;

	P.AddMonom(3,12);

	ASSERT_NO_THROW(Q=P);
}

TEST(Polinom, can_assign_to_itself)
{
	Polinom P;

	P.AddMonom(3,12);

	ASSERT_NO_THROW(P=P);
}

TEST(Polinom, it_has_its_own_memory)
{
	Polinom P;
	{
		Polinom Q;
		Q.AddMonom(3,12);
		P=Q;
	}

	EXPECT_EQ(1,!P.empty());
}

TEST(Polinom, can_exe_empty_pol)
{
	Polinom P;

	ASSERT_NO_THROW(P.Exe(4,3,1));
}

TEST(Polinom, can_exe)
{
	Polinom P;

	P.AddMonom(3,12);

	ASSERT_NO_THROW(P.Exe(4,2,1));
}

TEST(Polinom, empty_pol_equal_zero)
{
	Polinom P;

	ASSERT_NO_THROW(0, P.Exe(2,3,4));
}

TEST(Polinom, exe_pol)
{
	Polinom P;

	P.AddMonom(2,0);
	P.AddMonom(2,120);

	ASSERT_NO_THROW(10, P.Exe(2,2,5));
}

TEST(Polinom, can_add_empty_polinom)
{
	Polinom P,Q;

	ASSERT_NO_THROW(P+Q);
}

TEST(Polinom, can_add_polinom)
{
	Polinom P,Q;

	P.AddMonom(2,13);
	Q.AddMonom(1,0);

	ASSERT_NO_THROW(P+Q);
}

TEST(Polinom, right_add)
{
	Polinom P,Q,Res;
	
	P.AddMonom(1,0);
	P.AddMonom(1,100);
	P.AddMonom(1,110);
	//P=1+x+xy=7
	Q.AddMonom(1,100);
	Q.AddMonom(3,10);
	//Q=x+3y=6
	Res=P+Q;
	
	//x=3 y=1
	EXPECT_EQ(13, Res.Exe(3,1,0));
}

TEST(Polinom, add_with_invers_polinom)
{
	Polinom P,Q,Res;
	
	P.AddMonom(1,0);
	P.AddMonom(-1,100);
	P.AddMonom(1,110);
	//P=2-x+xy=8
	Q.AddMonom(-1,0);
	Q.AddMonom(1,100);
	Q.AddMonom(-1,110);
	//Q=-2+x-xy
	Res=P+Q;
	
	//x=3 y=1
	EXPECT_EQ(0, Res.Exe(3,1,0));
}

TEST(Polinom, can_sub_empty_polinom)
{
	Polinom P,Q;

	ASSERT_NO_THROW(P-Q);
}

TEST(Polinom, can_sub_polinom)
{
	Polinom P,Q;

	P.AddMonom(2,14);
	Q.AddMonom(1,0);

	ASSERT_NO_THROW(P-Q);
}

TEST(Polinom, right_sub)
{
	Polinom P,Q,Res;
	
	P.AddMonom(1,0);
	P.AddMonom(1,100);
	P.AddMonom(1,110);
	//P=1+x+xy=7
	Q.AddMonom(1,100);
	Q.AddMonom(3,10);
	//Q=x+3y=6
	Res=P-Q;
	
	//x=3 y=1
	EXPECT_EQ(1, Res.Exe(3,1,0));
}

TEST(Polinom, sub_with_itself)
{
	Polinom P,Res;
	
	P.AddMonom(1,0);
	P.AddMonom(-1,100);
	P.AddMonom(1,101);

	Res=P-P;
	
	//x=3 y=1
	EXPECT_EQ(0, Res.Exe(3,1,0));
}

TEST(Polinom, can_mul_on_monom)
{
	Polinom P;
	monom *m=new monom(4,15);

	P.AddMonom(-1,123);
	P.AddMonom(1,0);

	ASSERT_NO_THROW(P*m);
	delete m;
}

TEST(Polinom, right_mul_on_monom)
{
	Polinom P,Res;
	monom *m=new monom(2,10);

	//2y=2
	P.AddMonom(1,0);
	P.AddMonom(1,100);
	P.AddMonom(1,110);
	//P=1+x+xy=7
 	Res=P*m;
	//Res=P=4y+2xy+2xy^2=14
	
	//x=3 y=1
	EXPECT_EQ(14, Res.Exe(3,1,0));
}

TEST(Polinom, can_mul_polinom)
{
	Polinom P,Q;

	P.AddMonom(-2,123);
	Q.AddMonom(1,0);

	ASSERT_NO_THROW(P*Q);
}

TEST(Polinom, right_mul)
{
	Polinom P,Q,Res;
	
	P.AddMonom(3,100);
	P.AddMonom(-5,10);
	//P=3x-5y=-9
	Q.AddMonom(2,100);
	Q.AddMonom(1,10);
	//Q=2x+y=7
	Res=P*Q;
	
	//x=5 y=-1
	EXPECT_EQ(-84, Res.Exe(-1,5,0));
}
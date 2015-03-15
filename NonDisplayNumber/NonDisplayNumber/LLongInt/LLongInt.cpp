
#include "LLongInt.h"
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
int LLongInt::Trim( )
{
	int oldLen = lliLength;
	while ( pLLI[lliLength-1] == 0 && lliLength > 1)
		lliLength--;
	return (lliLength == oldLen );
}

//---------------------------------------------------------------------------------------------------

LLongInt::LLongInt()
{
	sign = 0;
	lliLength = 1;
	pLLI = new unsigned int[1];
	*pLLI = 0;
}

LLongInt::LLongInt(__int64 i64)
{
	pLLI = new unsigned int[2];
	lliLength = 2;
	if ( i64 < 0 )
	{
		sign = 1;
		i64 = -i64;
	}
	else
		sign = 0;
	memcpy(pLLI, &i64, 8);
	Trim( );
}

//---------------------------------------------------------------------------------------------------

LLongInt::LLongInt(char *strDec)
{
	if ( strDec[0] == '-' ) 
		sign = 1;
	else
		sign = 0;
	int strLen = strlen(strDec);
	if ( strLen % 4 == 0 )
		lliLength = strLen / 4;
	else
		lliLength = strLen / 4 + 1;
	pLLI = new unsigned int[lliLength];
	unsigned int *pTmp = new unsigned int[lliLength];
	memset(pLLI, 0, lliLength*4);
	memset(pTmp, 0, lliLength*4);
	unsigned int *pLLI = this->pLLI;
	int a, intCount;
	__asm
	{
		pusha
		mov ebx, this
		mov eax, [ebx][sign]
		mov dword ptr a, eax
WhileA1:
		mov edx, a
		mov intCount, edx
		shr intCount, 2
		inc intCount
		cmp edx, strLen
		jb LLIDec2Hex
		jmp LLIDec2HexOver
LLIDec2Hex:

		mov esi, 0
		mov ecx, intCount
CopyToTmp:
		mov eax, pLLI
		mov ebx, [eax][esi*4]
		mov eax, pTmp
		mov [eax][esi*4], ebx
		inc esi
		loop CopyToTmp

		mov eax, pLLI
		mov esi, intCount
		dec esi
EightTimes:
		cmp esi, 0
		jnz EightTimesLoop
		jmp EightTimesOver
EightTimesLoop:
		mov ebx, [eax][esi*4-4]
		shld [eax][esi*4], ebx, 3
		dec esi
		jmp EightTimes
EightTimesOver:
		shl dword ptr [eax][esi], 3

		mov eax, pTmp
		mov esi, intCount
		dec esi
TwoTimesTmp:
		cmp esi, 0
		jnz TwoTimesLoop
		jmp TwoTimesOver
TwoTimesLoop:
		mov ebx, [eax][esi*4-4]
		shld [eax][esi*4], ebx, 1
		dec esi
		jmp TwoTimesTmp
TwoTimesOver:
		shl dword ptr [eax][esi], 1

		mov ecx, intCount
		xor esi, esi
		clc
TenTimes:
		mov eax, pTmp
		mov ebx, [eax][esi*4]
		mov eax, pLLI
		adc [eax][esi*4], ebx
		inc esi
		loop TenTimes
		
		mov ecx, intCount
		mov esi, a
		xor eax, eax
		mov ebx, strDec
		mov al, byte ptr [ebx][esi];
		sub al, '0'
		xor esi, esi
		mov ebx, pLLI
		add [ebx][esi*4], eax
		inc esi
		dec ecx
		jnz AddDecBit
		jmp AddDecBitOver
AddDecBit:
		mov eax, pLLI
		adc dword ptr [eax][esi*4], 0
		inc esi
		loop AddDecBit
AddDecBitOver:
		inc a
		jmp WhileA1
LLIDec2HexOver:
		popa
	}
	Trim( );
	delete pTmp;
}

//---------------------------------------------------------------------------------------------------

LLongInt LLongInt::operator -( )
{
	__asm     //	sign = sign ^ 1;
	{
		mov eax, this
		xor dword ptr [eax][sign], 1
	}
	return *this;
}

LLongInt LLongInt::Abs(LLongInt &lli)
{
	return LLongInt(lli.pLLI, lli.lliLength, 0);
}

//---------------------------------------------------------------------------------------------------

LLongInt::LLongInt(unsigned int *strHex, int intCount, int sign)
{
	this->sign = sign;
	lliLength = intCount;
	pLLI = new unsigned int[intCount];
	memcpy(pLLI, strHex, intCount*4);
	Trim( );
}

//---------------------------------------------------------------------------------------------------

LLongInt::LLongInt(LLongInt &another)
{
	if ( &another == this )
		return;
	lliLength = another.lliLength;
	sign = another.sign;
	pLLI = new unsigned int[lliLength];
	memcpy(pLLI, another.pLLI, lliLength*4);
	Trim( );
}

//---------------------------------------------------------------------------------------------------

LLongInt::~LLongInt( )
{
	if ( pLLI != NULL )
		delete pLLI;
}

//---------------------------------------------------------------------------------------------------

LLongInt LLongInt::operator +(LLongInt &another)
{
	if ( sign != another.sign)
	{
		if ( sign == 0)
			return (*this-(-another));
		else
			return (another - (-*this));
	}
	int a, b, len;
	unsigned int *pSrcLLI;
	unsigned int *pResult;
	unsigned int *pAddLLI;
	if ( lliLength <= another.lliLength )
	{
		pResult = new unsigned int[another.lliLength+1];
		a = lliLength;
		b = another.lliLength + 1 - a;
		pSrcLLI = pLLI;
		pAddLLI = another.pLLI;
		len = another.lliLength;
	}
	else
	{
		pResult = new unsigned int[lliLength+1];
		a = another.lliLength;
		b = lliLength + 1 - a;
		pSrcLLI = another.pLLI;
		pAddLLI = pLLI;
		len = lliLength;
	}

	__asm
	{
		mov eax, pResult
		mov ebx, pSrcLLI
		xor esi, esi
		mov ecx, a
CopyToResult1:
		mov edx, [ebx][esi*4]
		mov [eax][esi*4], edx
		inc esi
		loop CopyToResult1

		mov ecx, b
ZeroResult1:
		mov dword ptr [eax][esi*4], 0
		inc esi
		loop ZeroResult1

		xor esi, esi
		mov ebx, pAddLLI
		mov ecx, len
		clc
AddLoop:
		mov edx, [ebx][esi*4]
		adc [eax][esi*4], edx
		inc esi
		loop AddLoop
		adc [eax][esi*4], 0
	}
	LLongInt rcLLI(pResult, len+1, sign);
	return rcLLI;
}

LLongInt LLongInt::operator -(LLongInt &another)
{
	if ( sign != another.sign )
		return (*this + (-another));
	if ( sign == 0 )
	{
		if ( *this < another )
			return -(another-*this);
	}
	else
	{
		if ( *this > another )
			return -(another-*this);
	}

	int a, b ;
	unsigned int *pSrcLLI;
	unsigned int *pResult;
	unsigned int *pSubLLI;

	pResult = new unsigned int[lliLength];
	a = another.lliLength;
	b = lliLength-another.lliLength;
	pSrcLLI = pLLI;
	pSubLLI = another.pLLI;

	__asm
	{
		mov eax, this
		mov ecx, [eax][lliLength]
		mov eax, pResult
		mov ebx, pSrcLLI
		xor esi, esi
CopyToResult1:
		mov edx, [ebx][esi*4]
		mov [eax][esi*4], edx
		inc esi
		loop CopyToResult1

		xor esi, esi
		mov ebx, pSubLLI
		mov ecx, a
		clc
SubLoop1:
		mov edx, [ebx][esi*4]
		sbb [eax][esi*4], edx
		inc esi
		loop SubLoop1

		mov ecx, b
		cmp ecx, 0
		jz SubOver
SubLoop2:
		sbb dword ptr [eax][esi*4], 0
		inc esi
		loop SubLoop2
SubOver:
	}
	LLongInt rcLLI(pResult, lliLength, sign);
	return rcLLI;
}

//---------------------------------------------------------------------------------------------------

LLongInt LLongInt::operator *(LLongInt &another)
{
	int rSign, tmpLen;
	unsigned int *rpLLI;
	unsigned int *pM1 = pLLI;
	unsigned int *pM2 = another.pLLI;
	int m1Len = lliLength;
	int m2Len = another.lliLength;
	__asm
	{
		;//���rSign
		mov eax, this
		mov ecx, [eax][sign]
		mov ebx, another
		xor ecx, [ebx][sign]
		mov rSign, ecx
		;//
		mov ecx, [eax][lliLength]
		add ecx, [ebx][lliLength]
		mov tmpLen, ecx
	}
	rpLLI = new unsigned int[tmpLen];
	__asm
	{
		;//���0
		mov eax, 0h
		mov edi, [rpLLI]
		mov ecx, tmpLen
		cld
		rep stosd

		mov esi, 0
while1:
		mov edi, 0
		cmp esi, m2Len
		jb while1Inner
		jmp while1Over
while1Inner:
while2:
		cmp edi, m1Len
		jb while2Inner
		jmp while2Over
while2Inner:
		mov eax, pM2
		mov ebx, [eax][esi*4]
		mov ecx, pM1
		mov eax, [ecx][edi*4]
		mul ebx
		mov ecx, esi
		add ecx, edi
		mov ebx, rpLLI
		add [ebx][ecx*4], eax
		inc ecx
		adc [ebx][ecx*4], edx
addForward:
		jnc addForwardOver
		inc ecx
		adc dword ptr [ebx][ecx*4], 0h
		jmp addForward
addForwardOver:
		inc edi
		jmp while2
while2Over:
		inc esi
		jmp while1
while1Over:
	}
	LLongInt rc(rpLLI, tmpLen, rSign);
	return rc;
}

//---------------------------------------------------------------------------------------------------
LLongInt LLongInt::operator /(LLongInt &another)
{
	unsigned int *pQuotient;
	int quotientLen;
	if (Abs(*this) >= Abs(another))
	{
	   quotientLen = this->lliLength - another.lliLength + 1;
       pQuotient = new unsigned int[quotientLen];
	}
	else
		return LLongInt((__int64)0);
	unsigned int *pQuotient2 = pQuotient + quotientLen - 1;
	unsigned int *pDivisorLLI = another.pLLI;
	unsigned int *pDivisorLLI2 = another.pLLI + another.lliLength - 1;
	unsigned int *pDividendLLI = new unsigned int[this->lliLength+2];
	unsigned int *pDividendLLI1 = pDividendLLI;
	unsigned int *pDividendLLI2;
	int divisorLZs /*, dividendLZs*/ ,rSign;
	int totalShiftBits, shiftedBits = 0;
	__asm
	{
		//���rSign
		mov eax, another
		mov ebx, this
		mov ecx, [eax][sign]
		xor ecx, [ebx][sign]
		mov rSign, ecx
		//����������
		mov edi, pDividendLLI
		mov ecx, [ebx][lliLength]
		mov dword ptr [edi][ecx*4], 0				;//�������˫����0
		mov dword ptr [edi][ecx*4+4], 0
		mov esi, [ebx][pLLI]
CopyDividend:
		mov edx, [esi][ecx*4-4]
		mov [edi][ecx*4-4], edx
		loop CopyDividend
		//
		mov ecx, [eax][lliLength]
		mov esi, [ebx][lliLength]
		dec esi
		shl esi, 2
		add esi, [ebx][pLLI]
		mov edi, pDivisorLLI2
CmpDividendDivisor1:
		mov edx, [esi]    ;//this->pLLI[esi]
		cmp edx, [edi]
		jb Fill32Zeros
		ja Fill64Zeros
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor1
		;//jmp Fill64Zeros                 ;//==
Fill64Zeros:
		add pDividendLLI1, 4
Fill32Zeros:
		mov ecx, [ebx][lliLength]
		sub ecx, [eax][lliLength]
		shl ecx, 2
		add pDividendLLI1, ecx
		//
		mov ecx, pDividendLLI1
		mov edx, [eax][lliLength]
		dec edx
		shl edx, 2
		add ecx, edx
		mov pDividendLLI2, ecx
		mov ecx, pDividendLLI1
		sub ecx, pDividendLLI
		shl ecx, 3
		mov totalShiftBits, ecx  //�ó�Ҫ��λ����λ��

		//��������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDivisorLLI2
		mov edi, [edi]   ;//another.pLLI[another.lliLength-1];
CalcDivisorLZLoop:
		test esi, edi
		jnz CalcDivisorLZOver
		inc edx
		shr esi, 1
		loop CalcDivisorLZLoop
CalcDivisorLZOver:
		mov divisorLZs, edx

;/*
;//����������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
;		mov ecx, 32
;		mov edx, 0
;		mov esi, 0x80000000
;		mov edi, [ebx][lliLength]
;		mov edi, [ebx][pLLI-4][edi*4]   ;//this->pLLI[this->lliLength-1];
;CalcDividendLZLoop0:
;		test esi, edi
;		jnz CalcDividendLZOver
;		inc edx
;		shr esi, 1
;		loop CalcDividendLZLoop
;CalcDividendLZOver0:
;		mov dividendLZs, edx
;*/

		//����Ϊ0
		mov edi, pQuotient
		push eax
		xor eax, eax  ;//mov eax, 0
		mov ecx, quotientLen
		cld
		rep stosd
		pop eax

LLongIntDivideLoop:
		//����������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDividendLLI2
		mov edi, [edi]
CalcDividendLZLoop:
		test esi, edi
		jnz CalcDividendLZOver
		inc edx
		shr esi, 1
		loop CalcDividendLZLoop
CalcDividendLZOver:
;//		mov dividendLZs, edx

;//����������max(1, dividendLZs-divisorLZs)λ
		mov ecx, 1
		;//mov edx, dividendLZs
		sub edx, divisorLZs
		cmp edx, 1
		jle DividendShiftLeft
		cmp edx, 32
		jb LessThan32Bits
		mov edx, 31
LessThan32Bits:
		mov ecx, edx
DividendShiftLeft:
		add shiftedBits, ecx
		mov edx, shiftedBits
		cmp edx, totalShiftBits
		jbe ShiftBitsOK
		sub shiftedBits, ecx
		mov edx, totalShiftBits
		sub edx, shiftedBits
		mov ecx, edx
		mov edx, totalShiftBits
		mov shiftedBits, edx
ShiftBitsOK:
		mov esi, pDividendLLI2
;//		cmp esi, pDividendLLI
;//		jb DividendShiftLeftOver
DividendShiftLeftLoop:
		mov edx, [esi]
		shld [esi+4], edx, cl
		sub esi, 4
		cmp esi, pDividendLLI
		jae DividendShiftLeftLoop
;//DividendShiftLeftOver:
		add esi, 4
		shl dword ptr [esi], cl

;//������max(1, dividendLZs-divisorLZs)λ
;//QuotientShiftLeft:
		mov esi, pQuotient2
		cmp esi, pQuotient
		jbe QuotientShiftLeftOver
QuotientShiftLeftLoop:
		mov edx, [esi-4]
		shld [esi], edx, cl
		sub esi, 4
		cmp esi, pQuotient
		ja QuotientShiftLeftLoop
QuotientShiftLeftOver:
		shl dword ptr [esi], cl
;//�Ƚϱ������ͳ�����...λ
		mov esi, pDividendLLI2
;//		add esi, 4
		cmp dword ptr [esi+4], 0
		ja SetQuotientTo1
;//		sub esi, 4
		mov ecx, [eax][lliLength]
		mov edi, pDivisorLLI2
CmpDividendDivisor2:
		mov edx, [esi]
		cmp edx, [edi]
		jb SetQuotientTo0
		ja SetQuotientTo1
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor2
SetQuotientTo1:
		mov esi, pQuotient
		or dword ptr [esi], 1

;//substraction
		mov esi, pDividendLLI1
		mov edi, pDivisorLLI
		mov ecx, [eax][lliLength]
		push eax
		xor eax, eax
		clc
SubDivisorFromDividend:
		mov edx, [edi][eax*4]
		sbb [esi][eax*4], edx
		inc eax
		loop SubDivisorFromDividend
		sbb [esi][eax*4], 0
		pop eax
;//		jmp SetQuotientOver
SetQuotientTo0:
;//SetQuotientOver:
		mov ecx, shiftedBits
		cmp ecx, totalShiftBits
		jb LLongIntDivideLoop
	}
	return LLongInt(pQuotient, quotientLen, rSign);
}

//---------------------------------------------------------------------------------------------------

LLongInt LLongInt::operator %(LLongInt &another)
{
	unsigned int *pQuotient;
	int quotientLen;
	if (Abs(*this) >= Abs(another))
	{
	   quotientLen = this->lliLength - another.lliLength + 1;
       pQuotient = new unsigned int[quotientLen];
	}
	else
		return *this;
	unsigned int *pQuotient2 = pQuotient + quotientLen - 1;
	unsigned int *pDivisorLLI = another.pLLI;
	unsigned int *pDivisorLLI2 = another.pLLI + another.lliLength - 1;
	unsigned int *pDividendLLI = new unsigned int[this->lliLength+2];
	unsigned int *pDividendLLI1 = pDividendLLI;
	unsigned int *pDividendLLI2;
	int divisorLZs /*, dividendLZs*/ ;
	int totalShiftBits, shiftedBits = 0;
	__asm
	{
		mov eax, another
		mov ebx, this
		//����������
		mov edi, pDividendLLI
		mov ecx, [ebx][lliLength]
		mov dword ptr [edi][ecx*4], 0				;//�������˫����0
		mov dword ptr [edi][ecx*4+4], 0
		mov esi, [ebx][pLLI]
CopyDividend:
		mov edx, [esi][ecx*4-4]
		mov [edi][ecx*4-4], edx
		loop CopyDividend
		//
		mov ecx, [eax][lliLength]
		mov esi, [ebx][lliLength]
		dec esi
		shl esi, 2
		add esi, [ebx][pLLI]
		mov edi, pDivisorLLI2
CmpDividendDivisor1:
		mov edx, [esi]    ;//this->pLLI[esi]
		cmp edx, [edi]
		jb Fill32Zeros
		ja Fill64Zeros
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor1
		;//jmp Fill64Zeros                 ;//==
Fill64Zeros:
		add pDividendLLI1, 4
Fill32Zeros:
		mov ecx, [ebx][lliLength]
		sub ecx, [eax][lliLength]
		shl ecx, 2
		add pDividendLLI1, ecx
		//
		mov ecx, pDividendLLI1
		mov edx, [eax][lliLength]
		dec edx
		shl edx, 2
		add ecx, edx
		mov pDividendLLI2, ecx
		mov ecx, pDividendLLI1
		sub ecx, pDividendLLI
		shl ecx, 3
		mov totalShiftBits, ecx  //�ó�Ҫ��λ����λ��

		//��������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDivisorLLI2
		mov edi, [edi]   ;//another.pLLI[another.lliLength-1];
CalcDivisorLZLoop:
		test esi, edi
		jnz CalcDivisorLZOver
		inc edx
		shr esi, 1
		loop CalcDivisorLZLoop
CalcDivisorLZOver:
		mov divisorLZs, edx

		//����Ϊ0
		mov edi, pQuotient
		push eax
		xor eax, eax  ;//mov eax, 0
		mov ecx, quotientLen
		cld
		rep stosd
		pop eax

LLongIntDivideLoop:
		//����������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDividendLLI2
		mov edi, [edi]
CalcDividendLZLoop:
		test esi, edi
		jnz CalcDividendLZOver
		inc edx
		shr esi, 1
		loop CalcDividendLZLoop
CalcDividendLZOver:
;//		mov dividendLZs, edx

;//����������max(1, dividendLZs-divisorLZs)λ
		mov ecx, 1
		;//mov edx, dividendLZs
		sub edx, divisorLZs
		cmp edx, 1
		jle DividendShiftLeft
		cmp edx, 32
		jb LessThan32Bits
		mov edx, 31
LessThan32Bits:
		mov ecx, edx
DividendShiftLeft:
		add shiftedBits, ecx
		mov edx, shiftedBits
		cmp edx, totalShiftBits
		jbe ShiftBitsOK
		sub shiftedBits, ecx
		mov edx, totalShiftBits
		sub edx, shiftedBits
		mov ecx, edx
		mov edx, totalShiftBits
		mov shiftedBits, edx
ShiftBitsOK:
		mov esi, pDividendLLI2
;//		cmp esi, pDividendLLI
;//		jb DividendShiftLeftOver
DividendShiftLeftLoop:
		mov edx, [esi]
		shld [esi+4], edx, cl
		sub esi, 4
		cmp esi, pDividendLLI
		jae DividendShiftLeftLoop
;//DividendShiftLeftOver:
		add esi, 4
		shl dword ptr [esi], cl

;//������max(1, dividendLZs-divisorLZs)λ
;//QuotientShiftLeft:
		mov esi, pQuotient2
		cmp esi, pQuotient
		jbe QuotientShiftLeftOver
QuotientShiftLeftLoop:
		mov edx, [esi-4]
		shld [esi], edx, cl
		sub esi, 4
		cmp esi, pQuotient
		ja QuotientShiftLeftLoop
QuotientShiftLeftOver:
		shl dword ptr [esi], cl
;//�Ƚϱ������ͳ�����...λ
		mov esi, pDividendLLI2
;//		add esi, 4
		cmp dword ptr [esi+4], 0
		ja SetQuotientTo1
;//		sub esi, 4
		mov ecx, [eax][lliLength]
		mov edi, pDivisorLLI2
CmpDividendDivisor2:
		mov edx, [esi]
		cmp edx, [edi]
		jb SetQuotientTo0
		ja SetQuotientTo1
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor2
SetQuotientTo1:
		mov esi, pQuotient
		or dword ptr [esi], 1

;//substraction
		mov esi, pDividendLLI1
		mov edi, pDivisorLLI
		mov ecx, [eax][lliLength]
		push eax
		xor eax, eax
		clc
SubDivisorFromDividend:
		mov edx, [edi][eax*4]
		sbb [esi][eax*4], edx
		inc eax
		loop SubDivisorFromDividend
		sbb [esi][eax*4], 0
		pop eax
;//		jmp SetQuotientOver
SetQuotientTo0:
;//SetQuotientOver:
		mov ecx, shiftedBits
		cmp ecx, totalShiftBits
		jb LLongIntDivideLoop
	}
	return LLongInt(pDividendLLI1, another.lliLength, this->sign);
}

//---------------------------------------------------------------------------------------------------

void LLongInt::operator =(LLongInt &another)
{
	if ( &another == this )
		return;
	if ( pLLI != NULL )
		delete pLLI;
	sign = another.sign;
	lliLength = another.lliLength;
	pLLI = new unsigned int[lliLength];
	memcpy(pLLI, another.pLLI, lliLength*4);
	Trim( );
	return;
}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator ==(LLongInt &another)
{
	if ( sign != another.sign || lliLength != another.lliLength )
		return 0;
	int rc = memcmp(pLLI, another.pLLI, lliLength*4);
	return ( rc == 0 );
}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator >(LLongInt &another)
{
	//���Ų���
	if ( sign == 1 && another.sign == 0 )
		return 0;
	if ( sign == 0 && another.sign == 1)
		return 1;
	//�������
	if ( sign == 0 && another.sign == 0 ) //��Ϊ����
	{
		//���Ȳ���
		if ( lliLength > another.lliLength )
			return 1;
		if ( lliLength < another.lliLength )
			return 0;
		//�������
		int a;
		for ( a=lliLength-1; a>=0; a-- )
		{
			if ( pLLI[a] == another.pLLI[a] )
				continue;
			return (pLLI[a] > another.pLLI[a]);
		}
	}
	else //��Ϊ����
	{
		//���Ȳ���
		if ( lliLength > another.lliLength )
			return 0;
		if ( lliLength < another.lliLength )
			return 1;
		//�������
		int a;
		for ( a=lliLength-1; a>=0; a-- )
		{
			if ( pLLI[a] == another.pLLI[a] )
				continue;
			return (pLLI[a] < another.pLLI[a]);
		}
	}
	//���
	return 0;
}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator <(LLongInt &another)
{
	//���Ų���
	if ( sign == 1 && another.sign == 0 )
		return 1;
	if ( sign == 0 && another.sign == 1)
		return 0;
	//�������
	if ( sign == 0 && another.sign == 0 ) //��Ϊ����
	{
		//���Ȳ���
		if ( lliLength > another.lliLength )
			return 0;
		if ( lliLength < another.lliLength )
			return 1;
		//�������
		int a;
		for ( a=lliLength-1; a>=0; a-- )
		{
			if ( pLLI[a] == another.pLLI[a] )
				continue;
			return (pLLI[a] < another.pLLI[a]);
		}
	}
	else //��Ϊ����
	{
		//���Ȳ���
		if ( lliLength > another.lliLength )
			return 1;
		if ( lliLength < another.lliLength )
			return 0;
		//�������
		int a;
		for ( a=lliLength-1; a>=0; a-- )
		{
			if ( pLLI[a] == another.pLLI[a] )
				continue;
			return (pLLI[a] > another.pLLI[a]);
		}
	}
	//���
	return 0;

}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator >=(LLongInt &another)
{
	return !(*this<another);
}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator <=(LLongInt &another)
{
	return !(*this>another);
}

//---------------------------------------------------------------------------------------------------

int LLongInt::operator !=(LLongInt &another)
{
	return !(*this==another);
}


LLongInt LLongInt::Divide(LLongInt &divisor, LLongInt &dividend, LLongInt &remainder)
{
	unsigned int *pQuotient;
	int quotientLen;
	if (Abs(dividend) >= Abs(divisor))
	{
	   quotientLen = dividend.lliLength - divisor.lliLength + 1;
       pQuotient = new unsigned int[quotientLen];
	}
	else
	{
		remainder = dividend;
		return LLongInt((__int64)0);
	}
	unsigned int *pQuotient2 = pQuotient + quotientLen - 1;
	unsigned int *pDivisorLLI = divisor.pLLI;
	unsigned int *pDivisorLLI2 = divisor.pLLI + divisor.lliLength - 1;
	unsigned int *pDividendLLI = new unsigned int[dividend.lliLength+2];
	unsigned int *pDividendLLI1 = pDividendLLI;
	unsigned int *pDividendLLI2;
	int divisorLZs/*, dividendLZs*/ , rSign;
	int totalShiftBits, shiftedBits = 0;
	__asm
	{
		//���rSign
		mov eax, divisor
		mov ebx, dividend
		mov ecx, [eax][sign]
		xor ecx, [ebx][sign]
		mov rSign, ecx
		//����������
		mov edi, pDividendLLI
		mov ecx, [ebx][lliLength]
		mov dword ptr [edi][ecx*4], 0				;//�������˫����0
		mov dword ptr [edi][ecx*4+4], 0
		mov esi, [ebx][pLLI]
CopyDividend:
		mov edx, [esi][ecx*4-4]
		mov [edi][ecx*4-4], edx
		loop CopyDividend
		//
		mov ecx, [eax][lliLength]
		mov esi, [ebx][lliLength]
		dec esi
		shl esi, 2
		add esi, [ebx][pLLI]
		mov edi, pDivisorLLI2
CmpDividendDivisor1:
		mov edx, [esi]    ;//this->pLLI[esi]
		cmp edx, [edi]
		jb Fill32Zeros
		ja Fill64Zeros
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor1
		;//jmp Fill64Zeros                 ;//==
Fill64Zeros:
		add pDividendLLI1, 4
Fill32Zeros:
		mov ecx, [ebx][lliLength]
		sub ecx, [eax][lliLength]
		shl ecx, 2
		add pDividendLLI1, ecx
		//
		mov ecx, pDividendLLI1
		mov edx, [eax][lliLength]
		dec edx
		shl edx, 2
		add ecx, edx
		mov pDividendLLI2, ecx
		mov ecx, pDividendLLI1
		sub ecx, pDividendLLI
		shl ecx, 3
		mov totalShiftBits, ecx  //�ó�Ҫ��λ����λ��

		//��������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDivisorLLI2
		mov edi, [edi]   ;//another.pLLI[another.lliLength-1];
CalcDivisorLZLoop:
		test esi, edi
		jnz CalcDivisorLZOver
		inc edx
		shr esi, 1
		loop CalcDivisorLZLoop
CalcDivisorLZOver:
		mov divisorLZs, edx

;/*
;//����������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
;		mov ecx, 32
;		mov edx, 0
;		mov esi, 0x80000000
;		mov edi, [ebx][lliLength]
;		mov edi, [ebx][pLLI-4][edi*4]   ;//this->pLLI[this->lliLength-1];
;CalcDividendLZLoop0:
;		test esi, edi
;		jnz CalcDividendLZOver
;		inc edx
;		shr esi, 1
;		loop CalcDividendLZLoop
;CalcDividendLZOver0:
;		mov dividendLZs, edx
;*/

		//����Ϊ0
		mov edi, pQuotient
		push eax
		xor eax, eax  ;//mov eax, 0
		mov ecx, quotientLen
		cld
		rep stosd
		pop eax

LLongIntDivideLoop:
		//����������ĵ�һ��˫�ֵ����λ�Ķ�����0�ĸ���
		mov ecx, 32
		mov edx, 0
		mov esi, 0x80000000
		mov edi, pDividendLLI2
		mov edi, [edi]
CalcDividendLZLoop:
		test esi, edi
		jnz CalcDividendLZOver
		inc edx
		shr esi, 1
		loop CalcDividendLZLoop
CalcDividendLZOver:
;//		mov dividendLZs, edx

;//����������max(1, dividendLZs-divisorLZs)λ
		mov ecx, 1
		;//mov edx, dividendLZs
		sub edx, divisorLZs
		cmp edx, 1
		jle DividendShiftLeft
		cmp edx, 32
		jb LessThan32Bits
		mov edx, 31
LessThan32Bits:
		mov ecx, edx
DividendShiftLeft:
		add shiftedBits, ecx
		mov edx, shiftedBits
		cmp edx, totalShiftBits
		jbe ShiftBitsOK
		sub shiftedBits, ecx
		mov edx, totalShiftBits
		sub edx, shiftedBits
		mov ecx, edx
		mov edx, totalShiftBits
		mov shiftedBits, edx
ShiftBitsOK:
		mov esi, pDividendLLI2
;//		cmp esi, pDividendLLI
;//		jb DividendShiftLeftOver
DividendShiftLeftLoop:
		mov edx, [esi]
		shld [esi+4], edx, cl
		sub esi, 4
		cmp esi, pDividendLLI
		jae DividendShiftLeftLoop
;//DividendShiftLeftOver:
		add esi, 4
		shl dword ptr [esi], cl

;//������max(1, dividendLZs-divisorLZs)λ
;//QuotientShiftLeft:
		mov esi, pQuotient2
		cmp esi, pQuotient
		jbe QuotientShiftLeftOver
QuotientShiftLeftLoop:
		mov edx, [esi-4]
		shld [esi], edx, cl
		sub esi, 4
		cmp esi, pQuotient
		ja QuotientShiftLeftLoop
QuotientShiftLeftOver:
		shl dword ptr [esi], cl
;//�Ƚϱ������ͳ�����...λ
		mov esi, pDividendLLI2
;//		add esi, 4
		cmp dword ptr [esi+4], 0
		ja SetQuotientTo1
;//		sub esi, 4
		mov ecx, [eax][lliLength]
		mov edi, pDivisorLLI2
CmpDividendDivisor2:
		mov edx, [esi]
		cmp edx, [edi]
		jb SetQuotientTo0
		ja SetQuotientTo1
		sub esi, 4
		sub edi, 4
		loop CmpDividendDivisor2
SetQuotientTo1:
		mov esi, pQuotient
		or dword ptr [esi], 1

;//substraction
		mov esi, pDividendLLI1
		mov edi, pDivisorLLI
		mov ecx, [eax][lliLength]
		push eax
		xor eax, eax
		clc
SubDivisorFromDividend:
		mov edx, [edi][eax*4]
		sbb [esi][eax*4], edx
		inc eax
		loop SubDivisorFromDividend
		sbb [esi][eax*4], 0
		pop eax
;//		jmp SetQuotientOver
SetQuotientTo0:
;//SetQuotientOver:
		mov ecx, shiftedBits
		cmp ecx, totalShiftBits
		jb LLongIntDivideLoop
	}
	remainder = LLongInt(pDividendLLI1, divisor.lliLength, dividend.sign);
	return LLongInt(pQuotient, quotientLen, rSign);
}
//---------------------------------------------------------------------------------------------------
char* LLongInt::LLongInt2A(char *buff, int radix, char *radixSymbols)
{
	static char strRadixSymbols[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'a', 'b', 'c', 'd', 'e', 'f'};
	if (radix <= 1)
		return NULL;
	if (radix > 16 && radixSymbols==NULL)
		return NULL;
	if (radix <=16 && radixSymbols==NULL)
		radixSymbols = strRadixSymbols;
	LLongInt zero((__int64)0);
	LLongInt divisor((__int64)radix);
	LLongInt quotient = *this;
	LLongInt remainder((__int64)0);
	int symbols = 0;
	char *pBuff;
	if (this->sign == 0)
		pBuff = buff;
	else
	{
		pBuff = buff + 1;
		buff[0] = '-';
	}
	if (quotient == zero)
	{
		pBuff[0] = radixSymbols[0];
		pBuff[1] = 0;
		return buff;
	}

	while (quotient != zero)
	{
		quotient = Divide(divisor, quotient, remainder);
		pBuff[symbols] = radixSymbols[remainder.pLLI[0]];
		symbols++;
	}
	pBuff[symbols] = 0;
	symbols--;
	int index = 0;
	char temp;
	while (index < symbols)
	{
		temp = pBuff[index];
		pBuff[index] = pBuff[symbols];
		pBuff[symbols] = temp;
		index++;
		symbols--;
	}
	return buff;
}

//ģ�ݳ��㷨, ���� *this ^ e mod n
LLongInt LLongInt::ExpMod(LLongInt e, LLongInt n)
{

	//����㷨
	//m = *this		���� m ^ e mod n
	int a, totalBits, nowBit, nowDW, testBits;
	LLongInt *pE = &e;
	LLongInt c(1);
	LLongInt m = *this;
	__asm
	{
	//����e���ж��ٸ�������λ
		mov eax, pE
		mov edx, [eax][lliLength]
		mov edi, edx
		shl edx, 5   ;//*32
		dec edi
		shl edi, 2   ;//*4

		mov ecx, 32
		mov esi, 0x80000000
		add edi, [eax][pLLI]
		mov edi, [edi]
CalcLZ:
		test esi, edi
		jnz CalcLZOver
		dec edx
		shr esi, 1
		loop CalcLZ
CalcLZOver:
		mov totalBits, edx
		mov dword ptr nowBit, 0
	}

	while (nowBit < totalBits)
	{
		__asm
		{
			mov esi, nowBit
			shr esi, 5    ;// /32
			shl esi, 2    ;// *4
			mov eax, pE
			add esi, [eax][pLLI]
			mov edx, [esi]
			mov nowDW, edx
			mov edx, totalBits
			sub edx, nowBit
			mov testBits, edx
			cmp edx, 32
			jbe TestHighestDWord
			;//mov testBits, 32
			jmp TestLowerDWords
		}
TestHighestDWord:
		for (a=0; a<testBits; a++)
		{
			__asm
			{
				test dword ptr nowDW, 1
				jz eDivide2
				;//and dword ptr nowDW, 0xfffffffe
			}
			c = ( m * c ) % n;
			__asm
			{
				mov edx, totalBits
				sub edx, nowBit
				cmp edx, 1
				jbe ExpModOver
			}
eDivide2:
			__asm	shr nowDW, 1
			m = (m * m) % n;
			__asm	inc nowBit
		}

TestLowerDWords:
		for (a=0; a<32; a++)
		{
			__asm
			{
				test dword ptr nowDW, 1
				jz eDivide2_2
				;//and dword ptr nowDW, 0xfffffffe
			}
			c = ( m * c ) % n;
eDivide2_2:
			__asm	shr nowDW, 1
			m = (m * m) % n;
			__asm	inc nowBit
		}
	}

ExpModOver:
	return c;


/*
	//C++�㷨
	LLongInt c(1);
	LLongInt m = *this;
	LLongInt zero((__int64)0);
	LLongInt one(1);
	LLongInt two(2);
	while ( e != zero)
	{
		if ( ( e % two ) == zero )
		{
			e = e / two;
			m = ( m * m ) % n;
		}
		else
		{
			e = e - one;
			c = ( m * c ) % n;
		}
	}
	return c;
*/

}






















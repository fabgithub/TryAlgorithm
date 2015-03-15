
class LLongInt
{
public:
	LLongInt();
	LLongInt(__int64 i64);
	LLongInt(char *strDec);
	LLongInt(unsigned int *strHex, int intCount, int sign);
	LLongInt(LLongInt &another);
	~LLongInt( );
	LLongInt operator +(LLongInt &another);
	LLongInt operator -( );
	LLongInt operator -(LLongInt &another);
	LLongInt operator *(LLongInt &another);
	LLongInt operator /(LLongInt &another);
	LLongInt operator %(LLongInt &another);
	LLongInt Abs(LLongInt &lli);
	void operator =(LLongInt &another);
	int operator ==(LLongInt &another);
	int operator >(LLongInt &another);
	int operator <(LLongInt &another);
	int operator >=(LLongInt &another);
	int operator <=(LLongInt &another);
	int operator !=(LLongInt &another);
	char* LLongInt2A(char *buff, int radix, char *radixSymbols=NULL);
	LLongInt ExpMod(LLongInt e, LLongInt n);	//ģ�ݳ��㷨
private:
	unsigned int *pLLI;
	int lliLength;  //int �ĸ���
	int sign;
private:
	int Trim( );
	LLongInt Divide(LLongInt &divisor, LLongInt &dividend, LLongInt &remainder);
};


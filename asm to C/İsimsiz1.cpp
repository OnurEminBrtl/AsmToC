#include <stdio.h>
#include <limits>

using namespace std;

#define k           8 
#define f           23
#define bias        ((1 << (k-1)) - 1)
#define expMask     ((1 << k) - 1)
#define fracMask    ((1 << f) - 1)

struct FloatValue {
private:    
    unsigned char signBit;
    unsigned char expValue;
    unsigned int fracValue;
    
public:    
    FloatValue(float value) 
    {
        unsigned int intValue = *(unsigned int*)(&value);
     
		signBit = (intValue >> 31) & 1;
        expValue = (intValue >> f) & expMask;
        fracValue = intValue & fracMask;
    }
    
    FloatValue(unsigned char signBit, unsigned char expValue, unsigned int fracValue) 
        : signBit{(unsigned char)(signBit & 1)}, expValue{expValue}, fracValue{fracValue & fracMask}
    {
        
    }
    
    unsigned char getSignBit() {
        return signBit;
    }
    
    unsigned char getExpValue() {
        return expValue;
    }
    
    int getE() {
        if (isDenormalized()) {
            return 1 - bias;
        }
        else if (isInf() || isNaN()) {
            return expMask;
        }
        else {
            return expValue - bias;
        }
    }

    unsigned int getFracValue() {
        return fracValue;
    }

    bool isDenormalized() {
        return expValue == 0 && fracValue != 0;
    }
    
    bool isInf() {
        return expValue == expMask && fracValue == 0;
    }
    
    bool isNaN() {
        return expValue == expMask && fracValue != 0;
    }
    
    bool isZero() {
        return expValue == 0 && fracValue == 0;
    }
    
    float value() {
        if (isZero()) {
            return 0.0f;
        }
        else if (isInf()) {
            return signBit ? -numeric_limits<float>::infinity() : numeric_limits<float>::infinity();
        }
        else if (isNaN()) {
            return numeric_limits<float>::quiet_NaN();
        }
        else {
            int e = getE();
            unsigned int frac = fracValue | (e == -bias ? 0 : 1 << f);
            unsigned int intValue = ((unsigned int)signBit << 31) | ((e + bias) << f) | frac;
            return *(float*)(&intValue);
        }
    }

};



int main()
{
    // Denormalized
    //struct FloatValue number(0.0f);
    //struct FloatValue number(0, 0, 0);
    //struct FloatValue number(0, 0, 0b00000000000000000000001);
    //struct FloatValue number(1.0f / 0.0f);
    //struct FloatValue number(-1.0f / 0.0f);
    //struct FloatValue number(numeric_limits<float>::quiet_NaN());
    //struct FloatValue number(0.0f / 0.0f);
    //struct FloatValue number(-0.0f / 0.0f);
    
    // Normalized
    struct FloatValue number(15213.0);
    //struct FloatValue number(0, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(-15213.0);
    //struct FloatValue number(1, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(15213.239258);
    //struct FloatValue number(-15213.239258);
    //struct FloatValue number(0.239258);
    //struct FloatValue number(-0.239258);

   
    printf("Float Value: %.50f \n", number.value());
    printf("Float Value: %e \n", number.value());
    printf("sign=%d, exp=%d (E=%d), frac=%d \n", number.getSignBit(), number.getExpValue(), number.getE(), number.getFracValue());
    printf("Is Denormalized : %d \n", number.isDenormalized());
    printf("Is Infinity : %d \n", number.isInf());
    printf("Is NaN : %d", number.isNaN());

    return 0;
}

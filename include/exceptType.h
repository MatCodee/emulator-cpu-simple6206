#ifndef  EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <iostream>
#include <stdexcept>
#include "except.h"


// Handler Error Aritmetic ADC Instruction
enum class ADCExceptionType {
	Overflow,
	SumOutOfRange,
	Generic,
};

class ADCRuntimeException : public std::runtime_error {
	public:
		ADCRuntimeException(ADCExceptionType errorType, const std::string& message)
			: ExceptionHandler(message), errorType_(errorType) {}
	
		ADCExceptionType getErrorType() const {
			return errorType_;
		}
	private:
		ADCExceptionType errorType_;
};






#endif // ! EXCEPTION_HANDLER_H



#ifndef  EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <iostream>
#include <stdexcept>
#include "opcode.h"
#include "types.h"

enum class InstructionErrorType {
	NotFound,
	NotImplemented,
};

// Exeptones de Instruccion de manera general
class InstructionException : public std::runtime_error {
	public:
		InstructionException(Emulator6502::Byte opcodeType, InstructionErrorType errorType, const std::string& message)
			: std::runtime_error(message), opcodeType_(opcodeType), errorType_(errorType) {}

	Emulator6502::Byte getInstructionType() const { return opcodeType_; }
	InstructionErrorType getErrorType() const { return errorType_; }

	private:
		Emulator6502::Byte opcodeType_;
		InstructionErrorType errorType_;
};


// Excepciones en tiempo de ejecucion
class ExceptionHandler : public std::runtime_error {
	public:	
		ExceptionHandler::ExceptionHandler(const std::string& message) : std::runtime_error(message) {}
};


#endif // ! EXCEPTION_HANDLER_H

#ifndef ERRORS_H
#define ERRORS_H

#include <exception>

namespace si {
	class SpaceInvadersException : std::exception {};

	// Errors for arguments
	class ArgumentError : SpaceInvadersException {
	public:
		virtual const char* what () const noexcept {
			return "You gave something unexpected as an argument.";
		}
	};
	class ArgumentShouldBeStrictPositive : ArgumentError {
	public:
		virtual const char* what () const noexcept {
			return "The argument you provided should have been sctricly positive.";
		}
	};
	class ArgumentShouldBePositive : ArgumentError {
	public:
		virtual const char* what () const noexcept {
			return "The argument you provided should have been positive.";
		}
	};

	// Screen errors
	class NotEnoughArgumentsError : ArgumentError {
	public:
		virtual const char* what () const noexcept {
			return "You tried constructing an object without providing enough arguments.";
		}
	};

	// Game errors
	class WorldSizeTooSmallError : ArgumentError {
	public:
		virtual const char* what () const noexcept {
			return "The worldsize you entered was too small.";
		}
	};

	// File errors
	class FileException : SpaceInvadersException {
	public:
		virtual const char* what () const noexcept {
			return "Something went wrong while trying to read or write to the provided file location.";
		}
	};
	class TextureFileException : FileException {
	public:
		virtual const char* what () const noexcept {
			return "Something went wrong while trying to read a texture file. Most likely this file does not exist.";
		}
	};
	class FontFileException : FileException {
	public:
		virtual const char* what () const noexcept {
			return "Something went wrong while trying to read the font file. Most likely this file does not exist.";
		}
	};
}

#endif /* ERRORS_H */
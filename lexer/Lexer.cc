#include<string>

// lexer returns tokens [0-255] if it is an unknown character
// or does not belong to these strings
enum token {
	// when eof occurs
	tok_eof = -1,

	// commands
	// when def keyword and extern keyword is encountered
	tok_def = -2,
	tok_extern = -3,

	// primary
	tok_identifier = -4,
	tok_number = -5,
};


static std::string IdentifierStr; // filled in if tok_identifier
static double NumVal; // filled in if tok_number
// above values have been declared as global, so they can be modified from anywhere within the code


/**
* gettok() - return the next token from standard input
*/
static int gettok() {

	// assign an integer value to whitespace, to initialize
	static int LastChar = ' ';

	// The isspace() function checks whether a character is a white-space character or not.
	// If an argument(character) passed to the isspace() function is a white - space character, 
	// it returns non - zero integer.If not, it returns 0.
	while (isspace(LastChar)) {

		// The C library function int getchar(void) gets a character (an unsigned char) from stdin. 
		// This is equivalent to getc with stdin as its argument.
		LastChar = getchar();
	}

	// isalpha(): checks whether a character is an alphabet or not
	if (isalpha(LastChar)) {
		IdentifierStr = LastChar;

		// isalnum(): checks whether character is alphanumeric
		while (isalnum(LastChar = getchar())) {
			IdentifierStr += LastChar;
		}

		if (IdentifierStr == "def")
			return tok_def;
		if (IdentifierStr == "extern")
			return tok_extern;
		return tok_identifier;
	}

	// lastchar is a digit. we will be returning a tok_number
	if ((isdigit(LastChar)) || (LastChar == '.')) {
		std::string NumStr;

		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while ((isdigit(LastChar)) || (LastChar == '.'));

		// strtod()
		// Parses the C-string str interpreting its content as a floating point number (according to the current locale) and returns its value as a double. 
		// If endptr is not a null pointer, the function also sets the value of endptr to point to the first character 
		// after the number.
		// The function first discards as many whitespace characters(as in isspace) as necessary 
		// until the first non - whitespace character is found.
		// Then, starting from this character, takes as many characters as possible that are valid following a syntax 
		// resembling that of floating point literals(see below), and interprets them as a numerical value. 
		// A pointer to the rest of the string after the last valid character is stored in the object pointed by endptr.
		NumVal = strtod(NumStr.c_str(), 0);

		return tok_number;
	}

	if (LastChar == '#') {
		// comment till end of line
		do
			LastChar = getchar();
		while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF)
			return gettok();
	}

	if (LastChar == EOF)
		return tok_eof;

	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}
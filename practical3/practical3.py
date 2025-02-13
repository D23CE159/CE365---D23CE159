# Lexical Analyzer
import os
import re

KEYWORDS = {"auto", "break", "case", "const", "char", "continue",
            "default", "do", "double", "else", "enum", "extern",
            "float", "for", "goto", "if", "inline", "int",  
            "long", "register", "restrict", "return", "short","signed",
            "sizeof", "static", "struct", "switch", "typedef", "union",
            "unsigned", "void", "volatile", "while", "_Bool", "_Complex",
            "_Imaginary"}

OPERATORS = {"+", "-", "*", "/", "%",
            "==", "!=", ">", "<", ">=", "<=",
            "&&", "||", "!",
            "&", "|", "^", "~", "<<", ">>",
            "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
            "++", "--",
            "? :",
            "->", ".", "(type)"}

DELIMITERS = {";", ",", "(", ")", "{", "}", "[", "]"}

# Symbol Table to store identifiers
symbol_table = {}

# for lexical error tracking
lexical_errors = []

def remove_comments(code):
    # Remove single-line and multi-line comments from the code
    code = re.sub(r"//.*", "", code)
    code = re.sub(r"/\*.*?\*/", "", code, flags = re.DOTALL)
    return code

def tokenize(code):
    # Tokenize the input code and line tracking
    tokens = []
    lines = code.splitlines()

    for line_num, line in enumerate(lines, start=1):
        lexemes = re.split(r'(\W)', line)
        for lex in lexemes:
            lex = lex.strip()
            if not lex:
                continue
            if lex in KEYWORDS:
                tokens.append((line_num, "KEYWORD", lex))
            elif lex in OPERATORS:
                tokens.append((line_num, "OPERATOR", lex))
            elif lex in DELIMITERS:
                tokens.append((line_num, "DELIMITER", lex))
            elif re.match(f"^[a-zA-Z_]\w*$", lex):
                if lex not in symbol_table:
                    symbol_table[lex] = {"type": "identifier", "line_declared": line_num}
                tokens.append((line_num, "IDENTIFIER", lex))
            elif re.match(r"^\d+(\.\d+)?$", lex):  # Match literals (integers/floats)
                tokens.append((line_num, "LITERAL", lex))
            else:
                lexical_errors.append((line_num, lex))  # Track lexical errors
    return tokens

def search_symbol_table(lexeme):
    # Search for the lexeme in the symbol table
    return symbol_table.get(lexeme, None)

def insert_or_update_symbol_table(lexeme, lexeme_type, line_num):
    """Insert a new lexeme or update an existing one in the symbol table."""
    if lexeme in symbol_table:
        # Update existing entry
        symbol_table[lexeme]["line_updated"] = line_num
    else:
        # Insert new entry
        symbol_table[lexeme] = {"type": lexeme_type, "line_declared": line_num}

def lexical_analyzer(file):
    # Perform lexical analysis on the input file
    if not file.endswith(".c"):
        raise ValueError("Input file must be a .c file")
    
    with open(file, 'r') as file:
        code = file.read()

    code = remove_comments(code)
    tokens = tokenize(code)
    return tokens

if __name__ == "__main__":
    file = input("Enter the path to the c file: ").strip()
    if not os.path.exists(file):
        print("Error: File does not exist")
    else:
        try:
            tokens = lexical_analyzer(file)
            print("Tokens: ")
            for token in tokens:
                print(f"Line {token[0]}: {token[1]} -> {token[2]}")

            print("\nSymbol Table: ")
            for lexeme, details in symbol_table.items():
                print(f"{lexeme}: {details}")

            # Display lexical errors
            if lexical_errors:
                print("\nLexical Errors:")
                for error in lexical_errors:
                    print(f"Line {error[0]}: Unrecognized token '{error[1]}'")
            else:
                print("\nNo lexical errors found.")

        except ValueError as e:
            print(e)
        except Exception as e:
            print(f"An unexpected error occurred: {e}")
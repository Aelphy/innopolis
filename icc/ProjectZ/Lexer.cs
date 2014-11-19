using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using QUT.Gppg;

namespace LexerAnalyzer
{
    public static class TypesHelper
    {
        public static int ToInt(this object o)
        {
            return (int)o;
        }
    }

    public enum Tokens
    {
        error = 2, EOF = 3, IDENTIFIER = 4, NUMBER = 5, CHARACTER = 6, // NOTE:CHARACTER WTF?
        STRING = 7, SEMICOLON = 8, DOT = 9, ASSIGN = 10, COMMA = 11, EQUAL = 12,
        COLON = 13, MULT = 14, PLUS = 15, MINUS = 16, LPAREN = 17, RPAREN = 18,
        VERT = 19, DOTDOT = 20, TILDE = 21, NON_EQUAL = 22, LESS = 23, LESS_EQUAL = 24,
        GREATER = 25, GREATER_EQUAL = 26, DIVIDE = 27, AMPERSAND = 28, LBRACKET = 29, RBRACKET = 30,
        CARET = 31, LBRACE = 32, RBRACE = 33, MODULE = 34, BEGIN = 35, END = 36,
        CONST = 37, TYPE = 38, VAR = 39, PROCEDURE = 40, ARRAY = 41, OF = 42,
        RECORD = 43, POINTER = 44, TO = 45, IF = 46, THEN = 47, CASE = 48,
        WHILE = 49, DO = 50, REPEAT = 51, UNTIL = 52, FOR = 53, LOOP = 54,
        WITH = 55, EXIT = 56, RETURN = 57, ELSIF = 58, ELSE = 59, BY = 60,
        NIL = 61, IN = 62, IS = 63, OR = 64, DIV = 65, MOD = 66,
        INTEGER = 67, REAL = 68, BOOLEAN = 69
    }

    class Lexer :
AbstractScanner<int, LexLocation>
    {
        LexLocation lex_location;
        StreamReader stream_reader;
        char last_sym;
        char last_sym_upper;
        bool eof;
        Dictionary<string, Tokens> keywords = new Dictionary<string, Tokens>();
        int line_index = 0;
        int line_number = 0;
        int prev_line_number = 0;
        int prev_line_index = 0;

        bool read_next_symbol()
        {
            char[] buffer = new char[1];

            prev_line_number = line_number;
            prev_line_index = line_index;

            if (stream_reader.Read(buffer, 0, 1) != 1)
            {
                if (last_sym == ' ')
                {
                    eof = true;
                    return false;
                }

                last_sym = ' ';
                last_sym_upper = ' ';

                return true;
            }

            if (buffer[0] == '\n')
            {
                last_sym = ' ';
                last_sym_upper = ' ';

                line_index = 0;
                ++line_number;
            } else
            {
                ++line_index;

                last_sym = buffer[0];
                last_sym_upper = char.ToUpperInvariant(last_sym);
            }


            return true;
        }

        int identifier_type(string identifier)
        {
            if (keywords.ContainsKey(identifier.ToUpperInvariant()))
            {
                return keywords[identifier.ToUpperInvariant()].ToInt();
            }

            return Tokens.IDENTIFIER.ToInt();
        }

        void fill_keywords()
        {
            keywords.Add("MODULE", Tokens.MODULE);
            keywords.Add("BEGIN", Tokens.BEGIN);
            keywords.Add("END", Tokens.END);
            keywords.Add("CONST", Tokens.CONST);
            keywords.Add("TYPE", Tokens.TYPE);
            keywords.Add("VAR", Tokens.VAR);
            keywords.Add("PROCEDURE", Tokens.PROCEDURE);
            keywords.Add("ARRAY", Tokens.ARRAY);
            keywords.Add("OF", Tokens.OF);
            keywords.Add("RECORD", Tokens.RECORD);
            keywords.Add("POINTER", Tokens.POINTER);
            keywords.Add("TO", Tokens.TO);
            keywords.Add("IF", Tokens.IF);
            keywords.Add("THEN", Tokens.THEN);
            keywords.Add("CASE", Tokens.CASE);
            keywords.Add("WHILE", Tokens.WHILE);
            keywords.Add("DO", Tokens.DO);
            keywords.Add("REPEAT", Tokens.REPEAT);
            keywords.Add("UNTIL", Tokens.UNTIL);
            keywords.Add("FOR", Tokens.FOR);
            keywords.Add("LOOP", Tokens.LOOP);
            keywords.Add("WITH", Tokens.WITH);
            keywords.Add("EXIT", Tokens.EXIT);
            keywords.Add("RETURN", Tokens.RETURN);
            keywords.Add("ELSIF", Tokens.ELSIF);
            keywords.Add("ELSE", Tokens.ELSE);
            keywords.Add("BY", Tokens.BY);
            keywords.Add("NIL", Tokens.NIL);
            keywords.Add("IN", Tokens.IN);
            keywords.Add("IS", Tokens.IS);
            keywords.Add("OR", Tokens.OR);
            keywords.Add("DIV", Tokens.DIV);
            keywords.Add("MOD", Tokens.MOD);
            keywords.Add("INTEGER", Tokens.INTEGER);
            keywords.Add("REAL", Tokens.REAL);
            keywords.Add("BOOLEAN", Tokens.BOOLEAN);

        }
        public Lexer(Stream stream)
        {
            lex_location = default(LexLocation);
            stream_reader = new StreamReader(stream);
            read_next_symbol();
            fill_keywords();
        }

        public override LexLocation yylloc
        {
            get
            {
                return lex_location;
            }

            set
            {
                this.lex_location = value;
            }
        }
        public override int yylex()
        {
            int sl, sc, el, ec;

            while (last_sym == ' ')
            {
                read_next_symbol();

                if (eof)
                {
                    return Tokens.EOF.ToInt();
                }
            }

            sl = prev_line_number;
            sc = prev_line_index;

            int rv = internal_yylex();

            el = prev_line_number;
            ec = prev_line_index;

            lex_location = new LexLocation(sl, sc, el, ec);

            Console.WriteLine("{0} at {1}:{2} .. {3}:{4}", (Tokens)rv, sl, sc, el, ec);

            return rv;
        }

        int internal_yylex()
        {
            if (eof)
            {
                return Tokens.EOF.ToInt();
            }

            if (char.IsLetter(last_sym) || last_sym == '_')
            {
                string identifier = "";

                while (char.IsLetterOrDigit(last_sym) || last_sym == '_')
                {
                    identifier += last_sym.ToString();
                    read_next_symbol();
                }

                return identifier_type(identifier);
            }

            if (char.IsDigit(last_sym))
            {
                read_next_symbol();

                while (char.IsDigit(last_sym) || (last_sym_upper >= 'A' && last_sym_upper <= 'F'))
                {
                    read_next_symbol();

                    if (last_sym_upper == 'H')
                    {
                        read_next_symbol();

                        return Tokens.NUMBER.ToInt();
                    }

                    if (last_sym == '.')
                    {
                        read_next_symbol();

                        if (char.IsDigit(last_sym))
                        {
                            read_next_symbol();

                            if (last_sym_upper == 'E')
                            {
                                read_next_symbol();

                                if (last_sym == '+' || last_sym == '-')
                                {
                                    read_next_symbol();
                                }

                                while (char.IsDigit(last_sym))
                                {
                                    read_next_symbol();
                                }

                                read_next_symbol();

                                return Tokens.NUMBER.ToInt();
                            }

                            return Tokens.error.ToInt();
                        }

                        return Tokens.error.ToInt();
                    }
                }

                return Tokens.NUMBER.ToInt();
            }


            switch (last_sym)
            {
                case '"':
                    do
                    {
                        read_next_symbol();
                    } while (last_sym != '"' && !eof);

                    if (!eof)
                    {
                        read_next_symbol();

                        return Tokens.STRING.ToInt();
                    }


                    return Tokens.error.ToInt();
                case ';':
                    read_next_symbol();

                    return Tokens.SEMICOLON.ToInt();
                case '=':
                    read_next_symbol();

                    return Tokens.EQUAL.ToInt();
                case ':':
                    read_next_symbol();

                    if (last_sym == '=')
                    {
                        read_next_symbol();

                        return Tokens.ASSIGN.ToInt();
                    }

                    return Tokens.COLON.ToInt();
                case '>':
                    read_next_symbol();

                    if (last_sym == '=')
                    {
                        read_next_symbol();

                        return Tokens.GREATER_EQUAL.ToInt();
                    }

                    return Tokens.GREATER.ToInt();
                case '<':
                    read_next_symbol();

                    if (last_sym == '=')
                    {
                        read_next_symbol();

                        return Tokens.LESS_EQUAL.ToInt();
                    }

                    return Tokens.LESS.ToInt();
                case '&':
                    read_next_symbol();

                    return Tokens.AMPERSAND.ToInt();
                case '^':
                    read_next_symbol();
                    return Tokens.CARET.ToInt();
                case '|':
                    read_next_symbol();
                    return Tokens.VERT.ToInt();
                case ',':
                    read_next_symbol();
                    return Tokens.COMMA.ToInt();
                case '.':
                    read_next_symbol();

                    if (last_sym == '.')
                    {
                        read_next_symbol();

                        return Tokens.DOTDOT.ToInt();
                    }

                    return Tokens.DOT.ToInt();
                case '{':
                    read_next_symbol();
                    return Tokens.LBRACE.ToInt();
                case '[':
                    read_next_symbol();
                    return Tokens.LBRACKET.ToInt();
                case '(':
                    read_next_symbol();
                    return Tokens.LPAREN.ToInt();
                case '-':
                    read_next_symbol();
                    return Tokens.MINUS.ToInt();
                case '#':
                    read_next_symbol();
                    return Tokens.NON_EQUAL.ToInt();
                case '+':
                    read_next_symbol();
                    return Tokens.PLUS.ToInt();
                case '}':
                    read_next_symbol();
                    return Tokens.RBRACE.ToInt();
                case ']':
                    read_next_symbol();
                    return Tokens.RBRACKET.ToInt();
                case ')':
                    read_next_symbol();
                    return Tokens.RPAREN.ToInt();
                case '~':
                    read_next_symbol();
                    return Tokens.TILDE.ToInt();
                case '/':
                    read_next_symbol();
                    return Tokens.DIVIDE.ToInt();
                case '*':
                    read_next_symbol();
                    return Tokens.MULT.ToInt();
            }

            return Tokens.error.ToInt();
        }
    }
}

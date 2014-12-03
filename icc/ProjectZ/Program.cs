using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using LexerAnalyzer;
using SyntaxParser;

namespace ProjectZ
{
    class Program
    {
        static void Main(string[] args)
        {
            // Чтобы вещественные числа распознавались и отображались в формате 3.14 (а не 3,14 как в русской Culture)
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");

            var fname = @"..\..\a.txt";
            Console.WriteLine(File.ReadAllText(fname));
            Console.WriteLine("-------------------------");

            Lexer lexer = new Lexer(new FileStream(fname, FileMode.Open));
            Parser parser = new Parser(lexer);
            Console.WriteLine("Parse: {0}", parser.Parse());
            //return;
            
            int tok = 0;
            while (true) {
                /*
                tok = scanner.yylex();
                if (tok == (int)Tok.EOF)
                    break;
                Console.WriteLine(scanner.TokToString((Tok)tok));
                 */
            };

            Console.ReadKey();
        }
    }
}

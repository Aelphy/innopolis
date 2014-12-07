// This code was generated by the Gardens Point Parser Generator
// Copyright (c) Wayne Kelly, John Gough, QUT 2005-2014
// (see accompanying GPPGcopyright.rtf)

// GPPG version 1.5.2
// Machine:  AELPHY
// DateTime: 16.11.2014 21:37:41
// UserName: Mikhail
// Input file <PROJECT.syntax - 25.10.2014 9:56:48>

// options: conflicts lines conflicts

using System;
using System.Collections.Generic;
using System.CodeDom.Compiler;
using System.Globalization;
using System.Text;
using QUT.Gppg;
using LexerAnalyzer;

namespace SyntaxParser
{
    [GeneratedCodeAttribute("Gardens Point Parser Generator", "1.5.2")]
    public class Parser : ShiftReduceParser<int, LexLocation>
    {
#pragma warning disable 649
        private static Dictionary<int, string> aliases;
#pragma warning restore 649
        private static Rule[] rules = new Rule[154];
        private static State[] states = new State[281];
        private static string[] nonTerms = new string[] {
      "Compilation", "$accept", "Module", "ModuleBody", "StatementSeq", "DeclarationSeq", 
      "Declaration", "SimpleDeclarationSeq", "SimpleDeclaration", "ProcedureDeclaration", 
      "ConstantDeclarationList", "TypeDeclarationList", "VariableDeclarationList", 
      "ConstantDeclaration", "DefiningIdentifier", "Expression", "TypeDeclaration", 
      "Type", "VariableDeclaration", "DefiningIdentifierList", "ProcedureHead", 
      "ProcedureBody", "Receiver", "FormalParameters", "FPSectionSeq", "QualifiedIdentifier", 
      "FPSection", "IdentifierList", "ExpressionList", "Fields", "FieldListSeq", 
      "FieldList", "Statement", "Designator", "ElsifClauseSeq", "CaseClauseList", 
      "GuardClauseSeq", "ElsifClause", "CaseClause", "CaseLabelList", "CaseLabel", 
      "GuardClause", "SimpleExpression", "RelationalOperator", "SignOpt", "Term", 
      "AdditiveTermSeq", "AdditiveOperator", "Factor", "MultiplicativeFactorSeq", 
      "MultiplicativeOperator", "DesignatorTailSeq", "DesignatorTail", };

        public Parser(AbstractScanner<int, LexLocation> scanner) : base(scanner) {}

        static Parser()
        {
            states[0] = new State(new int[] { 34, 4 }, new int[] { -1, 1, -3, 280 });
            states[1] = new State(new int[] { 3, 2, 34, 4 }, new int[] { -3, 3 });
            states[2] = new State(-1);
            states[3] = new State(-3);
            states[4] = new State(new int[] { 4, 5 });
            states[5] = new State(new int[] { 63, 6 });
            states[6] = new State(new int[] { 35, 10, 37, 165, 38, 177, 39, 240, 40, 250, 36, -5 }, new int[] { -4, 7, -6, 160, -7, 279, -9, 164, -10, 249 });
            states[7] = new State(new int[] { 36, 8 });
            states[8] = new State(new int[] { 4, 9 });
            states[9] = new State(-4);
            states[10] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74 }, new int[] { -5, 11, -33, 90, -34, 14 });
            states[11] = new State(new int[] { 8, 12, 36, -6 });
            states[12] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74, 59, -74, 58, -74, 52, -74, 19, -74 }, new int[] { -33, 13, -34, 14 });
            states[13] = new State(-73);
            states[14] = new State(new int[] { 10, 15, 17, 78, 8, -76, 36, -76, 59, -76, 58, -76, 52, -76, 19, -76 });
            states[15] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 16, -43, 17, -45, 20 });
            states[16] = new State(-75);
            states[17] = new State(new int[] { 12, 70, 22, 71, 23, 72, 24, 73, 25, 74, 26, 75, 62, 76, 63, 77, 8, -107, 36, -107, 59, -107, 58, -107, 52, -107, 19, -107, 18, -107, 11, -107, 30, -107, 42, -107, 47, -107, 20, -107, 13, -107, 54, -107 }, new int[] { -44, 18 });
            states[18] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -43, 19, -45, 20 });
            states[19] = new State(-108);
            states[20] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -46, 21, -49, 25, -34, 29 });
            states[21] = new State(new int[] { 15, 65, 16, 66, 64, 67, 12, -109, 22, -109, 23, -109, 24, -109, 25, -109, 26, -109, 62, -109, 63, -109, 8, -109, 36, -109, 59, -109, 58, -109, 52, -109, 19, -109, 18, -109, 11, -109, 30, -109, 42, -109, 47, -109, 20, -109, 13, -109, 54, -109 }, new int[] { -47, 22, -48, 68 });
            states[22] = new State(new int[] { 15, 65, 16, 66, 64, 67, 12, -110, 22, -110, 23, -110, 24, -110, 25, -110, 26, -110, 62, -110, 63, -110, 8, -110, 36, -110, 59, -110, 58, -110, 52, -110, 19, -110, 18, -110, 11, -110, 30, -110, 42, -110, 47, -110, 20, -110, 13, -110, 54, -110 }, new int[] { -48, 23 });
            states[23] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -46, 24, -49, 25, -34, 29 });
            states[24] = new State(-115);
            states[25] = new State(new int[] { 14, 58, 27, 59, 65, 60, 66, 61, 28, 62, 15, -116, 16, -116, 64, -116, 12, -116, 22, -116, 23, -116, 24, -116, 25, -116, 26, -116, 62, -116, 63, -116, 8, -116, 36, -116, 59, -116, 58, -116, 52, -116, 19, -116, 18, -116, 11, -116, 30, -116, 42, -116, 47, -116, 20, -116, 13, -116, 54, -116 }, new int[] { -50, 26, -51, 63 });
            states[26] = new State(new int[] { 14, 58, 27, 59, 65, 60, 66, 61, 28, 62, 15, -117, 16, -117, 64, -117, 12, -117, 22, -117, 23, -117, 24, -117, 25, -117, 26, -117, 62, -117, 63, -117, 8, -117, 36, -117, 59, -117, 58, -117, 52, -117, 19, -117, 18, -117, 11, -117, 30, -117, 42, -117, 47, -117, 20, -117, 13, -117, 54, -117 }, new int[] { -51, 27 });
            states[27] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -49, 28, -34, 29 });
            states[28] = new State(-119);
            states[29] = new State(new int[] { 17, 30, 14, -120, 27, -120, 65, -120, 66, -120, 28, -120, 15, -120, 16, -120, 64, -120, 12, -120, 22, -120, 23, -120, 24, -120, 25, -120, 26, -120, 62, -120, 63, -120, 8, -120, 36, -120, 59, -120, 58, -120, 52, -120, 19, -120, 18, -120, 11, -120, 30, -120, 42, -120, 47, -120, 20, -120, 13, -120, 54, -120 });
            states[30] = new State(new int[] { 18, 31, 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -29, 32, -16, 38, -43, 17, -45, 20 });
            states[31] = new State(-121);
            states[32] = new State(new int[] { 18, 33, 11, 34 });
            states[33] = new State(-122);
            states[34] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 35, -43, 17, -45, 20 });
            states[35] = new State(-66);
            states[36] = new State(-112);
            states[37] = new State(-113);
            states[38] = new State(-65);
            states[39] = new State(new int[] { 9, 42, 29, 44, 31, 47, 10, -145, 17, -145, 8, -145, 36, -145, 59, -145, 58, -145, 52, -145, 19, -145, 14, -145, 27, -145, 65, -145, 66, -145, 28, -145, 15, -145, 16, -145, 64, -145, 12, -145, 22, -145, 23, -145, 24, -145, 25, -145, 26, -145, 62, -145, 63, -145, 18, -145, 11, -145, 30, -145, 42, -145, 47, -145, 20, -145, 13, -145, 54, -145 }, new int[] { -52, 40, -53, 48 });
            states[40] = new State(new int[] { 9, 42, 29, 44, 31, 47, 10, -146, 17, -146, 8, -146, 36, -146, 59, -146, 58, -146, 52, -146, 19, -146, 14, -146, 27, -146, 65, -146, 66, -146, 28, -146, 15, -146, 16, -146, 64, -146, 12, -146, 22, -146, 23, -146, 24, -146, 25, -146, 26, -146, 62, -146, 63, -146, 18, -146, 11, -146, 30, -146, 42, -146, 47, -146, 20, -146, 13, -146, 54, -146 }, new int[] { -53, 41 });
            states[41] = new State(-148);
            states[42] = new State(new int[] { 4, 43 });
            states[43] = new State(-149);
            states[44] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -29, 45, -16, 38, -43, 17, -45, 20 });
            states[45] = new State(new int[] { 30, 46, 11, 34 });
            states[46] = new State(-150);
            states[47] = new State(-151);
            states[48] = new State(-147);
            states[49] = new State(-123);
            states[50] = new State(-124);
            states[51] = new State(-125);
            states[52] = new State(-126);
            states[53] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 54, -43, 17, -45, 20 });
            states[54] = new State(new int[] { 18, 55 });
            states[55] = new State(-127);
            states[56] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -49, 57, -34, 29 });
            states[57] = new State(-128);
            states[58] = new State(-140);
            states[59] = new State(-141);
            states[60] = new State(-142);
            states[61] = new State(-143);
            states[62] = new State(-144);
            states[63] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -49, 64, -34, 29 });
            states[64] = new State(-118);
            states[65] = new State(-137);
            states[66] = new State(-138);
            states[67] = new State(-139);
            states[68] = new State(new int[] { 4, 39, 5, 49, 6, 50, 7, 51, 61, 52, 17, 53, 21, 56 }, new int[] { -46, 69, -49, 25, -34, 29 });
            states[69] = new State(-114);
            states[70] = new State(-129);
            states[71] = new State(-130);
            states[72] = new State(-131);
            states[73] = new State(-132);
            states[74] = new State(-133);
            states[75] = new State(-134);
            states[76] = new State(-135);
            states[77] = new State(-136);
            states[78] = new State(new int[] { 18, 79, 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -29, 80, -16, 38, -43, 17, -45, 20 });
            states[79] = new State(-77);
            states[80] = new State(new int[] { 18, 81, 11, 34 });
            states[81] = new State(-78);
            states[82] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 83, -43, 17, -45, 20 });
            states[83] = new State(new int[] { 47, 84 });
            states[84] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 59, -74, 8, -74, 58, -74 }, new int[] { -5, 85, -33, 90, -34, 14 });
            states[85] = new State(new int[] { 36, 86, 59, 87, 8, 12, 58, 155 }, new int[] { -35, 149, -38, 159 });
            states[86] = new State(-79);
            states[87] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 88, -33, 90, -34, 14 });
            states[88] = new State(new int[] { 36, 89, 8, 12 });
            states[89] = new State(-80);
            states[90] = new State(-72);
            states[91] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 92, -43, 17, -45, 20 });
            states[92] = new State(new int[] { 42, 93 });
            states[93] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -36, 94, -39, 148, -40, 139, -41, 147, -16, 144, -43, 17, -45, 20 });
            states[94] = new State(new int[] { 36, 95, 59, 96, 19, 137 });
            states[95] = new State(-83);
            states[96] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 97, -33, 90, -34, 14 });
            states[97] = new State(new int[] { 36, 98, 8, 12 });
            states[98] = new State(-84);
            states[99] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 100, -43, 17, -45, 20 });
            states[100] = new State(new int[] { 54, 101 });
            states[101] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 102, -33, 90, -34, 14 });
            states[102] = new State(new int[] { 36, 103, 8, 12 });
            states[103] = new State(-85);
            states[104] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 52, -74, 8, -74 }, new int[] { -5, 105, -33, 90, -34, 14 });
            states[105] = new State(new int[] { 36, 106, 52, 107, 8, 12 });
            states[106] = new State(-86);
            states[107] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 108, -43, 17, -45, 20 });
            states[108] = new State(new int[] { 36, 109 });
            states[109] = new State(-87);
            states[110] = new State(new int[] { 4, 111 });
            states[111] = new State(new int[] { 62, 112 });
            states[112] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 113, -43, 17, -45, 20 });
            states[113] = new State(new int[] { 20, 114 });
            states[114] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 115, -43, 17, -45, 20 });
            states[115] = new State(new int[] { 54, 116 });
            states[116] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 117, -33, 90, -34, 14 });
            states[117] = new State(new int[] { 36, 118, 8, 12 });
            states[118] = new State(-88);
            states[119] = new State(new int[] { 4, 133 }, new int[] { -37, 120, -42, 136, -26, 130 });
            states[120] = new State(new int[] { 36, 121, 59, 122, 19, 128 });
            states[121] = new State(-89);
            states[122] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 123, -33, 90, -34, 14 });
            states[123] = new State(new int[] { 36, 124, 8, 12 });
            states[124] = new State(-90);
            states[125] = new State(-91);
            states[126] = new State(new int[] { 15, 36, 16, 37, 8, -92, 36, -92, 59, -92, 58, -92, 52, -92, 19, -92, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 127, -43, 17, -45, 20 });
            states[127] = new State(-93);
            states[128] = new State(new int[] { 4, 133 }, new int[] { -42, 129, -26, 130 });
            states[129] = new State(-105);
            states[130] = new State(new int[] { 13, 131 });
            states[131] = new State(new int[] { 4, 133 }, new int[] { -26, 132 });
            states[132] = new State(-106);
            states[133] = new State(new int[] { 9, 134, 13, -152, 36, -152, 59, -152, 19, -152, 8, -152, 11, -152, 18, -152, 63, -152 });
            states[134] = new State(new int[] { 4, 135 });
            states[135] = new State(-153);
            states[136] = new State(-104);
            states[137] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -39, 138, -40, 139, -41, 147, -16, 144, -43, 17, -45, 20 });
            states[138] = new State(-98);
            states[139] = new State(new int[] { 13, 140, 11, 142 });
            states[140] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74, 59, -74, 19, -74 }, new int[] { -5, 141, -33, 90, -34, 14 });
            states[141] = new State(new int[] { 8, 12, 36, -99, 59, -99, 19, -99 });
            states[142] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -41, 143, -16, 144, -43, 17, -45, 20 });
            states[143] = new State(-101);
            states[144] = new State(new int[] { 20, 145, 13, -102, 11, -102 });
            states[145] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 146, -43, 17, -45, 20 });
            states[146] = new State(-103);
            states[147] = new State(-100);
            states[148] = new State(-97);
            states[149] = new State(new int[] { 36, 150, 59, 151, 58, 155 }, new int[] { -38, 154 });
            states[150] = new State(-81);
            states[151] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 36, -74, 8, -74 }, new int[] { -5, 152, -33, 90, -34, 14 });
            states[152] = new State(new int[] { 36, 153, 8, 12 });
            states[153] = new State(-82);
            states[154] = new State(-95);
            states[155] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 156, -43, 17, -45, 20 });
            states[156] = new State(new int[] { 47, 157 });
            states[157] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74, 59, -74, 58, -74 }, new int[] { -5, 158, -33, 90, -34, 14 });
            states[158] = new State(new int[] { 8, 12, 36, -96, 59, -96, 58, -96 });
            states[159] = new State(-94);
            states[160] = new State(new int[] { 35, 162, 37, 165, 38, 177, 39, 240, 40, 250, 36, -7 }, new int[] { -7, 161, -9, 164, -10, 249 });
            states[161] = new State(-10);
            states[162] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74 }, new int[] { -5, 163, -33, 90, -34, 14 });
            states[163] = new State(new int[] { 8, 12, 36, -8 });
            states[164] = new State(-13);
            states[165] = new State(new int[] { 4, 173 }, new int[] { -11, 166, -14, 176, -15, 170 });
            states[166] = new State(new int[] { 8, 167, 11, 168 });
            states[167] = new State(-15);
            states[168] = new State(new int[] { 4, 173 }, new int[] { -14, 169, -15, 170 });
            states[169] = new State(-19);
            states[170] = new State(new int[] { 12, 171 });
            states[171] = new State(new int[] { 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -16, 172, -43, 17, -45, 20 });
            states[172] = new State(-20);
            states[173] = new State(new int[] { 14, 174, 16, 175, 12, -29, 63, -29, 13, -29, 11, -29, 17, -29, 8, -29 });
            states[174] = new State(-30);
            states[175] = new State(-31);
            states[176] = new State(-18);
            states[177] = new State(new int[] { 4, 173 }, new int[] { -12, 178, -17, 239, -15, 182 });
            states[178] = new State(new int[] { 8, 179, 11, 180 });
            states[179] = new State(-16);
            states[180] = new State(new int[] { 4, 173 }, new int[] { -17, 181, -15, 182 });
            states[181] = new State(-22);
            states[182] = new State(new int[] { 63, 183 });
            states[183] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 184, -26, 188 });
            states[184] = new State(-23);
            states[185] = new State(-54);
            states[186] = new State(-55);
            states[187] = new State(-56);
            states[188] = new State(-57);
            states[189] = new State(new int[] { 42, 190, 15, 36, 16, 37, 4, -111, 5, -111, 6, -111, 7, -111, 61, -111, 17, -111, 21, -111 }, new int[] { -29, 236, -16, 38, -43, 17, -45, 20 });
            states[190] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 191, -26, 188 });
            states[191] = new State(-58);
            states[192] = new State(new int[] { 17, 195, 4, 173, 36, -67 }, new int[] { -30, 193, -31, 200, -32, 235, -20, 203, -15, 234 });
            states[193] = new State(new int[] { 36, 194 });
            states[194] = new State(-60);
            states[195] = new State(new int[] { 4, 133 }, new int[] { -26, 196 });
            states[196] = new State(new int[] { 18, 197 });
            states[197] = new State(new int[] { 4, 173, 36, -67 }, new int[] { -30, 198, -31, 200, -32, 235, -20, 203, -15, 234 });
            states[198] = new State(new int[] { 36, 199 });
            states[199] = new State(-61);
            states[200] = new State(new int[] { 8, 201, 36, -68 });
            states[201] = new State(new int[] { 4, 173 }, new int[] { -32, 202, -20, 203, -15, 234 });
            states[202] = new State(-70);
            states[203] = new State(new int[] { 13, 204, 11, 232 });
            states[204] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 205, -26, 188 });
            states[205] = new State(-71);
            states[206] = new State(new int[] { 45, 207 });
            states[207] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 208, -26, 188 });
            states[208] = new State(-62);
            states[209] = new State(new int[] { 17, 211, 8, -63, 11, -63, 36, -63, 18, -63 }, new int[] { -24, 210 });
            states[210] = new State(-64);
            states[211] = new State(new int[] { 18, 212, 4, 226, 39, 227 }, new int[] { -25, 215, -27, 231, -28, 221 });
            states[212] = new State(new int[] { 13, 213, 8, -44, 11, -44, 36, -44, 18, -44, 63, -44 });
            states[213] = new State(new int[] { 4, 133 }, new int[] { -26, 214 });
            states[214] = new State(-46);
            states[215] = new State(new int[] { 18, 216, 8, 219 });
            states[216] = new State(new int[] { 13, 217, 8, -45, 11, -45, 36, -45, 18, -45, 63, -45 });
            states[217] = new State(new int[] { 4, 133 }, new int[] { -26, 218 });
            states[218] = new State(-47);
            states[219] = new State(new int[] { 4, 226, 39, 227 }, new int[] { -27, 220, -28, 221 });
            states[220] = new State(-49);
            states[221] = new State(new int[] { 13, 222, 11, 224 });
            states[222] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 223, -26, 188 });
            states[223] = new State(-50);
            states[224] = new State(new int[] { 4, 225 });
            states[225] = new State(-53);
            states[226] = new State(-52);
            states[227] = new State(new int[] { 4, 226 }, new int[] { -28, 228 });
            states[228] = new State(new int[] { 13, 229, 11, 224 });
            states[229] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 230, -26, 188 });
            states[230] = new State(-51);
            states[231] = new State(-48);
            states[232] = new State(new int[] { 4, 173 }, new int[] { -15, 233 });
            states[233] = new State(-28);
            states[234] = new State(-27);
            states[235] = new State(-69);
            states[236] = new State(new int[] { 42, 237, 11, 34 });
            states[237] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 238, -26, 188 });
            states[238] = new State(-59);
            states[239] = new State(-21);
            states[240] = new State(new int[] { 4, 173 }, new int[] { -13, 241, -19, 248, -20, 245, -15, 234 });
            states[241] = new State(new int[] { 8, 242, 11, 243 });
            states[242] = new State(-17);
            states[243] = new State(new int[] { 4, 173 }, new int[] { -19, 244, -20, 245, -15, 234 });
            states[244] = new State(-25);
            states[245] = new State(new int[] { 13, 246, 11, 232 });
            states[246] = new State(new int[] { 67, 185, 68, 186, 69, 187, 4, 133, 41, 189, 43, 192, 44, 206, 40, 209 }, new int[] { -18, 247, -26, 188 });
            states[247] = new State(-26);
            states[248] = new State(-24);
            states[249] = new State(-14);
            states[250] = new State(new int[] { 4, 173, 17, 269 }, new int[] { -21, 251, -15, 264, -23, 266 });
            states[251] = new State(new int[] { 63, 252, 8, 263 });
            states[252] = new State(new int[] { 35, 256, 37, 165, 38, 177, 39, 240, 36, -40 }, new int[] { -22, 253, -8, 258, -9, 262 });
            states[253] = new State(new int[] { 36, 254 });
            states[254] = new State(new int[] { 4, 255 });
            states[255] = new State(-32);
            states[256] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74 }, new int[] { -5, 257, -33, 90, -34, 14 });
            states[257] = new State(new int[] { 8, 12, 36, -41 });
            states[258] = new State(new int[] { 35, 260, 37, 165, 38, 177, 39, 240, 36, -42 }, new int[] { -9, 259 });
            states[259] = new State(-12);
            states[260] = new State(new int[] { 4, 39, 46, 82, 48, 91, 49, 99, 54, 104, 53, 110, 55, 119, 56, 125, 57, 126, 8, -74, 36, -74 }, new int[] { -5, 261, -33, 90, -34, 14 });
            states[261] = new State(new int[] { 8, 12, 36, -43 });
            states[262] = new State(-11);
            states[263] = new State(-33);
            states[264] = new State(new int[] { 17, 211, 63, -34, 8, -34 }, new int[] { -24, 265 });
            states[265] = new State(-36);
            states[266] = new State(new int[] { 4, 173 }, new int[] { -15, 267 });
            states[267] = new State(new int[] { 17, 211, 63, -35, 8, -35 }, new int[] { -24, 268 });
            states[268] = new State(-37);
            states[269] = new State(new int[] { 4, 270, 39, 274 });
            states[270] = new State(new int[] { 13, 271 });
            states[271] = new State(new int[] { 4, 272 });
            states[272] = new State(new int[] { 18, 273 });
            states[273] = new State(-38);
            states[274] = new State(new int[] { 4, 275 });
            states[275] = new State(new int[] { 13, 276 });
            states[276] = new State(new int[] { 4, 277 });
            states[277] = new State(new int[] { 18, 278 });
            states[278] = new State(-39);
            states[279] = new State(-9);
            states[280] = new State(-2);

            for (int sNo = 0; sNo < states.Length; sNo++) states[sNo].number = sNo;

            rules[1] = new Rule(-2, new int[] { -1, 3 });
            rules[2] = new Rule(-1, new int[] { -3 });
            rules[3] = new Rule(-1, new int[] { -1, -3 });
            rules[4] = new Rule(-3, new int[] { 34, 4, 63, -4, 36, 4 });
            rules[5] = new Rule(-4, new int[] { });
            rules[6] = new Rule(-4, new int[] { 35, -5 });
            rules[7] = new Rule(-4, new int[] { -6 });
            rules[8] = new Rule(-4, new int[] { -6, 35, -5 });
            rules[9] = new Rule(-6, new int[] { -7 });
            rules[10] = new Rule(-6, new int[] { -6, -7 });
            rules[11] = new Rule(-8, new int[] { -9 });
            rules[12] = new Rule(-8, new int[] { -8, -9 });
            rules[13] = new Rule(-7, new int[] { -9 });
            rules[14] = new Rule(-7, new int[] { -10 });
            rules[15] = new Rule(-9, new int[] { 37, -11, 8 });
            rules[16] = new Rule(-9, new int[] { 38, -12, 8 });
            rules[17] = new Rule(-9, new int[] { 39, -13, 8 });
            rules[18] = new Rule(-11, new int[] { -14 });
            rules[19] = new Rule(-11, new int[] { -11, 11, -14 });
            rules[20] = new Rule(-14, new int[] { -15, 12, -16 });
            rules[21] = new Rule(-12, new int[] { -17 });
            rules[22] = new Rule(-12, new int[] { -12, 11, -17 });
            rules[23] = new Rule(-17, new int[] { -15, 63, -18 });
            rules[24] = new Rule(-13, new int[] { -19 });
            rules[25] = new Rule(-13, new int[] { -13, 11, -19 });
            rules[26] = new Rule(-19, new int[] { -20, 13, -18 });
            rules[27] = new Rule(-20, new int[] { -15 });
            rules[28] = new Rule(-20, new int[] { -20, 11, -15 });
            rules[29] = new Rule(-15, new int[] { 4 });
            rules[30] = new Rule(-15, new int[] { 4, 14 });
            rules[31] = new Rule(-15, new int[] { 4, 16 });
            rules[32] = new Rule(-10, new int[] { 40, -21, 63, -22, 36, 4 });
            rules[33] = new Rule(-10, new int[] { 40, -21, 8 });
            rules[34] = new Rule(-21, new int[] { -15 });
            rules[35] = new Rule(-21, new int[] { -23, -15 });
            rules[36] = new Rule(-21, new int[] { -15, -24 });
            rules[37] = new Rule(-21, new int[] { -23, -15, -24 });
            rules[38] = new Rule(-23, new int[] { 17, 4, 13, 4, 18 });
            rules[39] = new Rule(-23, new int[] { 17, 39, 4, 13, 4, 18 });
            rules[40] = new Rule(-22, new int[] { });
            rules[41] = new Rule(-22, new int[] { 35, -5 });
            rules[42] = new Rule(-22, new int[] { -8 });
            rules[43] = new Rule(-22, new int[] { -8, 35, -5 });
            rules[44] = new Rule(-24, new int[] { 17, 18 });
            rules[45] = new Rule(-24, new int[] { 17, -25, 18 });
            rules[46] = new Rule(-24, new int[] { 17, 18, 13, -26 });
            rules[47] = new Rule(-24, new int[] { 17, -25, 18, 13, -26 });
            rules[48] = new Rule(-25, new int[] { -27 });
            rules[49] = new Rule(-25, new int[] { -25, 8, -27 });
            rules[50] = new Rule(-27, new int[] { -28, 13, -18 });
            rules[51] = new Rule(-27, new int[] { 39, -28, 13, -18 });
            rules[52] = new Rule(-28, new int[] { 4 });
            rules[53] = new Rule(-28, new int[] { -28, 11, 4 });
            rules[54] = new Rule(-18, new int[] { 67 });
            rules[55] = new Rule(-18, new int[] { 68 });
            rules[56] = new Rule(-18, new int[] { 69 });
            rules[57] = new Rule(-18, new int[] { -26 });
            rules[58] = new Rule(-18, new int[] { 41, 42, -18 });
            rules[59] = new Rule(-18, new int[] { 41, -29, 42, -18 });
            rules[60] = new Rule(-18, new int[] { 43, -30, 36 });
            rules[61] = new Rule(-18, new int[] { 43, 17, -26, 18, -30, 36 });
            rules[62] = new Rule(-18, new int[] { 44, 45, -18 });
            rules[63] = new Rule(-18, new int[] { 40 });
            rules[64] = new Rule(-18, new int[] { 40, -24 });
            rules[65] = new Rule(-29, new int[] { -16 });
            rules[66] = new Rule(-29, new int[] { -29, 11, -16 });
            rules[67] = new Rule(-30, new int[] { });
            rules[68] = new Rule(-30, new int[] { -31 });
            rules[69] = new Rule(-31, new int[] { -32 });
            rules[70] = new Rule(-31, new int[] { -31, 8, -32 });
            rules[71] = new Rule(-32, new int[] { -20, 13, -18 });
            rules[72] = new Rule(-5, new int[] { -33 });
            rules[73] = new Rule(-5, new int[] { -5, 8, -33 });
            rules[74] = new Rule(-33, new int[] { });
            rules[75] = new Rule(-33, new int[] { -34, 10, -16 });
            rules[76] = new Rule(-33, new int[] { -34 });
            rules[77] = new Rule(-33, new int[] { -34, 17, 18 });
            rules[78] = new Rule(-33, new int[] { -34, 17, -29, 18 });
            rules[79] = new Rule(-33, new int[] { 46, -16, 47, -5, 36 });
            rules[80] = new Rule(-33, new int[] { 46, -16, 47, -5, 59, -5, 36 });
            rules[81] = new Rule(-33, new int[] { 46, -16, 47, -5, -35, 36 });
            rules[82] = new Rule(-33, new int[] { 46, -16, 47, -5, -35, 59, -5, 36 });
            rules[83] = new Rule(-33, new int[] { 48, -16, 42, -36, 36 });
            rules[84] = new Rule(-33, new int[] { 48, -16, 42, -36, 59, -5, 36 });
            rules[85] = new Rule(-33, new int[] { 49, -16, 54, -5, 36 });
            rules[86] = new Rule(-33, new int[] { 54, -5, 36 });
            rules[87] = new Rule(-33, new int[] { 54, -5, 52, -16, 36 });
            rules[88] = new Rule(-33, new int[] { 53, 4, 62, -16, 20, -16, 54, -5, 36 });
            rules[89] = new Rule(-33, new int[] { 55, -37, 36 });
            rules[90] = new Rule(-33, new int[] { 55, -37, 59, -5, 36 });
            rules[91] = new Rule(-33, new int[] { 56 });
            rules[92] = new Rule(-33, new int[] { 57 });
            rules[93] = new Rule(-33, new int[] { 57, -16 });
            rules[94] = new Rule(-35, new int[] { -38 });
            rules[95] = new Rule(-35, new int[] { -35, -38 });
            rules[96] = new Rule(-38, new int[] { 58, -16, 47, -5 });
            rules[97] = new Rule(-36, new int[] { -39 });
            rules[98] = new Rule(-36, new int[] { -36, 19, -39 });
            rules[99] = new Rule(-39, new int[] { -40, 13, -5 });
            rules[100] = new Rule(-40, new int[] { -41 });
            rules[101] = new Rule(-40, new int[] { -40, 11, -41 });
            rules[102] = new Rule(-41, new int[] { -16 });
            rules[103] = new Rule(-41, new int[] { -16, 20, -16 });
            rules[104] = new Rule(-37, new int[] { -42 });
            rules[105] = new Rule(-37, new int[] { -37, 19, -42 });
            rules[106] = new Rule(-42, new int[] { -26, 13, -26 });
            rules[107] = new Rule(-16, new int[] { -43 });
            rules[108] = new Rule(-16, new int[] { -43, -44, -43 });
            rules[109] = new Rule(-43, new int[] { -45, -46 });
            rules[110] = new Rule(-43, new int[] { -45, -46, -47 });
            rules[111] = new Rule(-45, new int[] { });
            rules[112] = new Rule(-45, new int[] { 15 });
            rules[113] = new Rule(-45, new int[] { 16 });
            rules[114] = new Rule(-47, new int[] { -48, -46 });
            rules[115] = new Rule(-47, new int[] { -47, -48, -46 });
            rules[116] = new Rule(-46, new int[] { -49 });
            rules[117] = new Rule(-46, new int[] { -49, -50 });
            rules[118] = new Rule(-50, new int[] { -51, -49 });
            rules[119] = new Rule(-50, new int[] { -50, -51, -49 });
            rules[120] = new Rule(-49, new int[] { -34 });
            rules[121] = new Rule(-49, new int[] { -34, 17, 18 });
            rules[122] = new Rule(-49, new int[] { -34, 17, -29, 18 });
            rules[123] = new Rule(-49, new int[] { 5 });
            rules[124] = new Rule(-49, new int[] { 6 });
            rules[125] = new Rule(-49, new int[] { 7 });
            rules[126] = new Rule(-49, new int[] { 61 });
            rules[127] = new Rule(-49, new int[] { 17, -16, 18 });
            rules[128] = new Rule(-49, new int[] { 21, -49 });
            rules[129] = new Rule(-44, new int[] { 12 });
            rules[130] = new Rule(-44, new int[] { 22 });
            rules[131] = new Rule(-44, new int[] { 23 });
            rules[132] = new Rule(-44, new int[] { 24 });
            rules[133] = new Rule(-44, new int[] { 25 });
            rules[134] = new Rule(-44, new int[] { 26 });
            rules[135] = new Rule(-44, new int[] { 62 });
            rules[136] = new Rule(-44, new int[] { 63 });
            rules[137] = new Rule(-48, new int[] { 15 });
            rules[138] = new Rule(-48, new int[] { 16 });
            rules[139] = new Rule(-48, new int[] { 64 });
            rules[140] = new Rule(-51, new int[] { 14 });
            rules[141] = new Rule(-51, new int[] { 27 });
            rules[142] = new Rule(-51, new int[] { 65 });
            rules[143] = new Rule(-51, new int[] { 66 });
            rules[144] = new Rule(-51, new int[] { 28 });
            rules[145] = new Rule(-34, new int[] { 4 });
            rules[146] = new Rule(-34, new int[] { 4, -52 });
            rules[147] = new Rule(-52, new int[] { -53 });
            rules[148] = new Rule(-52, new int[] { -52, -53 });
            rules[149] = new Rule(-53, new int[] { 9, 4 });
            rules[150] = new Rule(-53, new int[] { 29, -29, 30 });
            rules[151] = new Rule(-53, new int[] { 31 });
            rules[152] = new Rule(-26, new int[] { 4 });
            rules[153] = new Rule(-26, new int[] { 4, 9, 4 });
        }

        protected override void Initialize()
        {
            this.InitSpecialTokens((int)Tokens.error, (int)Tokens.EOF);
            this.InitStates(states);
            this.InitRules(rules);
            this.InitNonTerminals(nonTerms);
        }

        protected override void DoAction(int action)
        {
#pragma warning disable 162, 1522
            switch (action)
            {
            }
#pragma warning restore 162, 1522
        }

        protected override string TerminalToString(int terminal)
        {
            if (aliases != null && aliases.ContainsKey(terminal))
                return aliases[terminal];
            else if (((Tokens)terminal).ToString() != terminal.ToString(CultureInfo.InvariantCulture))
                return ((Tokens)terminal).ToString();
            else
                return CharToString((char)terminal);
        }

#line 378 "PROJECT.syntax"
        // =========================================================================

#line default
    }
}
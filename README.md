--> Built a recursive descent parser for Jack language.

--> Jack is a simple object-based language(without inheritance) with a Java-like syntax.
		You can find more about jack in the following given link
		https://www.csie.ntu.edu.tw/~cyy/courses/introCS/18fall/lectures/handouts/lec13_Jack.pdf

--> The input to this parser is a jack file.

--> The challenge is to check whether the input jack file is syntactically correct or not.
		If not it gives you an appropriate message with a specified line number.

--> In general, a parser does both syntax and semantic analysis. The semantic analysis deals 
		with the expressions whether an expression derives any meaning or not. But here we are only 
		dealing with syntax analysis.

--> Here, we consider a simple form of recursive-descent parsing, called predictive parsing, in which the lookahead 
		symbol determines the flow of control through the procedure.

--> Programming-language parsers almost always make a single left-to-right scan over the input, looking ahead one 
		terminal at a time, and checking for the grammar. 

--> The input jack file should not contain multiple statements in a single line because this parser 
		cannot handle multiple statements in a single line.

--> Make sure that both the files named Main2.jack and Parser_final.cpp must be in the same directory.

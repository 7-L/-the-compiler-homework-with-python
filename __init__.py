# -*- coding: utf-8 -*-  
#--------------------------------------------------------------------------  
#Author:7-L
#date: 2016-5-19
#--------------------------------------------------------------------------  
import lex


#lexpos - Current position in the input string
#lexstate - Current lexer state
#lexstatestack - Stack of lexer states
#lexstateinfo - State information
#lexerrorf - Error rule (if any)
  tokens = [
    "TOKEN_IDENT",  
    "TOKEN_INT",  
    "TOKEN_FLOAT",  
  #  "TOKEN_STRING",
    "TOKEN_OP",  
    "TOKEN_DELIM_COMMA",        #,  
    "TOKEN_DELIM_OPEN_PAREN",   #(  
    "TOKEN_DELIM_CLOSE_PAREN",  #)  
    "TOKEN_DELIM_OPEN_BRACKET", #[  
    "TOKEN_DELIM_CLOSE_BRACKET",#]  
    "TOKEN_DELIM_OPEN_BRACE",   #{  
    "TOKEN_DELIM_CLOSE_BRACE",  #}  
    "TOKEN_DELIM_SEMICOLON",    #;
    "TOKEN_DELIM_COLON",        #:
    "TOKEN_DELIM_NumberSign"   # #
       
    ]  
   
reserved = {  
   'if'     :   'TOKEN_RSRVD_IF',  
   'else'   :   'TOKEN_RSRVD_ELSE',  
   'true'   :   'TOKEN_RSRVD_TRUE',  
   'false'  :   'TOKEN_RSRVD_FALSE',  
   'while'  :   'TOKEN_RSRVD_WHILE',  
   'break'  :   'TOKEN_RSRVD_BREAK',  
   'continue':  'TOKEN_RSRVD_CONTINUE',  
   'goto'   :   'TOKEN_RSRVD_GOTO',  
   'func'   :   'TOKEN_RSRVD_FUNC',  
   'var'    :   'TOKEN_RSRVD_VAR',  
   'for'    :   'TOKEN_RSRVD_FOR',  
   'return' :   'TOKEN_RSRVD_RETURN' 
}  
   
tokens += reserved .values()  
   
   
t_ignore = r' \t\r'
def t_COMMENT(t):  
    r'(/\*(.|\n)*?\*/)|(\/\/.*)'
    pass 
   
def t_newline(t):  
    r'\n+' 
    t.lexer.lineno += len(t.value)  
       
def t_error(t):  
    print "LaunchScript error: "+repr(t.value)  
       
def t_TOKEN_IDENT(t):  
    r'[a-zA-Z_][a-zA-Z_0-9]*' #标识符  
    t.type = reserved.get(t.value , 'TOKEN_IDENT')  
    return t  
   
def t_TOKEN_INT(t):  
    r'(0x[a-fA-F0-9]+)|([0-9]+)' 
    return t  
   
t_TOKEN_FLOAT =  r'[0-9]*\.[0-9]+' 
#t_TOKEN_STRING = r'(\"([^\\\r]|(\\.))*?\")' #|(\"([^\\\n]|(\\.))*?\")' only for windows
t_TOKEN_DELIM_COMMA = r'\,' 
t_TOKEN_DELIM_OPEN_PAREN = r'\(' 
t_TOKEN_DELIM_CLOSE_PAREN = r'\)' 
t_TOKEN_DELIM_OPEN_BRACKET = r'\[' 
t_TOKEN_DELIM_CLOSE_BRACKET = r'\]' 
t_TOKEN_DELIM_OPEN_BRACE = r'\{' 
t_TOKEN_DELIM_CLOSE_BRACE = r'\}' 
t_TOKEN_DELIM_SEMICOLON = r'\;'
t_TOKEN_DELIM_COLON = r'\:'
t_TOKEN_DELIM_NumberSign = r'\#'
   
def t_TOKEN_OP(t):  
    r'(\<\<\=)|(\>\>\=)|([\+\-\*\/\%\&\|\^\=\!\>\<]\=)|(\|\|)|(\&\&)|(\+\+)|(\-\-)|[\+\-\*\/\%\^\=\&\|\>\<\!\~]' 
    return t  
   
   
   
       
if __name__ == "__main__":  
    lexer = lex.lex()  
    f = open("./test.txt" , 'rb')  
    data = f.read()  
    f.close()  
    lexer.input(data)  
   
    while True:  
        tok = lexer.token()  
        if not tok: break      # No more input  
        print tok.value+"\t---->\t"+tok.type
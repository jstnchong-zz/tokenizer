/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//follow the FSM

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char* stringInp; //input string
    char* curr; //current token
    int error; //indicator if current token is an error
    size_t strLength; // length of token
    int cursor; //position of cursor in string
};

typedef struct TokenizerT_ TokenizerT;



/*
 * TKCreate creates stream[i]new TokenizerT object for stream[i]given token stream
 * (given as stream[i]string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change to increase efficiency.)
 * If the function succeeds, it returns stream[i]non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts )
{
    TokenizerT* tokenizer = (TokenizerT*) malloc(sizeof(TokenizerT));
    tokenizer->strLength = strlen(ts);
    
    if(tokenizer->strLength == 0)
    {
        return NULL;
    }
    tokenizer->error = 0;
    tokenizer->cursor = 0;
    tokenizer->stringInp = (char*)malloc(sizeof(char)*(1+tokenizer->strLength));
    strcpy(tokenizer->stringInp, ts);
    tokenizer->curr = (char*)malloc(sizeof(char)*(1+tokenizer->strLength));
    //strcpy(tokenizer->tokenizer->curr, ts);
    
    
    return tokenizer;
}

/*
 * TKDestroy destroys stream[i]TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk->stringInp);
    free(tk->curr);
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns stream[i]C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    
    char* ret; //token string to be returned
    ret = (char*)malloc(sizeof(char));
    
    char* stream = (char*)malloc(sizeof(char)*(1+tk->strLength)); //original string
    strcpy(stream, tk->stringInp);
    
    int i; //increments the cursor
    i = tk->cursor;
    
    int j; //increments the return character array
    j = 0;
    
    
    while(stream[i] == ' ' || stream[i] == '\t' || stream[i] == '\v' || stream[i] == '\t' || stream[i] == '\f' || stream[i] == '\r' || stream[i] == '\n' ) {
        i++;
    }
    
    
    
    if (isalpha(stream[i]))
    {
        while(isalnum(stream[i]))
        {
            ret[j] = stream[i];
            i++;
            j++;
        }
        tk->cursor = i;
        
        printf("word ");
        return ret;
    }
    
    if (isdigit(stream[i]))
    {
        //Handles tokens starting with the digit 0
        if(stream[i] == '0')
        {
            if (stream[i+1] <= '7' && stream[i+1] >= '0')// octal
            {
                while(stream[i] <= '7' && stream[i] >= '0')
                {
                    ret[j] = stream[i];
                    i++;
                    j++;
                }
                tk->cursor = i;
                
                printf("octal constant ");
                return ret;
            }
            
            if (stream[i+1] == 'x' || stream[i+1] == 'X')// hex
            {
                if(isxdigit(stream[i+2]))
                {
                    while(j<2)
                    {
                        ret[j] = stream[i];
                        j++;
                        i++;
                    }
                    
                    while(isxdigit(stream[i]))
                    {
                    ret[j] = stream[i];
                    i++;
                    j++;
                    }
                    
                    tk->cursor = i;
                    
                    printf("hex constant ");
                    return ret;
                }
                
                else
                {
                    while(j<3)
                    {
                        ret[j] = stream[i];
                        j++;
                        i++;
                    }
                
                        tk->cursor = i;
                        
                        printf("error malformed input: ");
                        return ret;
                    }
                }
            }
        
            if (stream[i+1]== '.')
            {
                if(isdigit(stream[i+2]))
                {
                    while(j<2)
                    {
                        ret[j] = stream[i];
                        j++;
                        i++;
                    }
                    while(isdigit(stream[i]))
                    {
                        ret[j] = stream[i];
                        i++;
                        j++;
                    }
                    
                    if(stream[i] == 'E' || stream[i] == 'e')
                    {
                        if(stream[i+1] == '+' || stream[i+1] == '-')
                        {
                            
                            if(isdigit(stream[i+2]))
                            {
                                for(int k = 0; k<2; k++)
                                {
                                    ret[j] = stream[i];
                                    j++;
                                    i++;
                                }
                                
        
                                while(isdigit(stream[i]))
                                {
                                    ret[j] = stream[i];
                                    i++;
                                    j++;
                                }
                                
                                tk->cursor = i;
                                
                                printf("float ");
                                return ret;
                                   
                            }
                            
                            else
                            {
                                for(int k = 0; k<3; k++)
                                {
                                    ret[j] = stream[i];
                                    j++;
                                    i++;
                                }
                                   
                                tk->cursor = i;
                                   
                                printf("error malformed input: ");
                                return ret;
                            }
                        }
                               
                        else
                        {
                            if(isdigit(stream[i+1]))
                               {
                                   for(int k = 0; k<2; k++)
                                   {
                                       ret[j] = stream[i];
                                       j++;
                                       i++;
                                   }
                                   while(isdigit(stream[i]))
                                   {
                                       ret[j] = stream[i];
                                       i++;
                                       j++;
                                   }
                                   
                                   tk->cursor = i;
                                   
                                   printf("float ");
                                   return ret;
                                   
                               }
                               
                               else
                               {
                                   for(int k = 0; k<2; k++)
                                   {
                                       ret[j] = stream[i];
                                       j++;
                                       i++;
                                   }
                                   
                                   tk->cursor = i;
                                   
                                   printf("error malformed input: ");
                                   return ret;
                               }

                        }
                               
                    }
                    
                    tk->cursor = i;
                    
                    printf("float ");
                    return ret;
                }
            }

        
        
        //handles tokens starting with digits 1-9
        else
        {
            while(isdigit(stream[i]))
            {
                ret[j] = stream[i];
                i++;
                j++;
            }
            
            if (stream[i]== '.' || stream[i]== 'E' || stream[i] == 'e')
            {
                if(stream[i] == 'E' || stream[i] == 'e')
                {
                    if(stream[i+1] == '+' || stream[i+1] == '-')
                    {
                        
                        if(isdigit(stream[i+2]))
                        {
                            for(int l = 0; l<2; l++)
                            {
                                ret[j] = stream[i];
                                j++;
                                i++;
                            }
                            
                            
                            while(isdigit(stream[i]))
                            {
                                ret[j] = stream[i];
                                i++;
                                j++;
                            }
                            
                            tk->cursor = i;
                            
                            printf("float ");
                            return ret;
                            
                        }
                        
                        else
                        {
                            for(int l = 0; l<3; l++)
                            {
                                ret[j] = stream[i];
                                j++;
                                i++;
                            }
                            
                            tk->cursor = i;
                            
                            printf("error malformed input: ");
                            return ret;
                        }
                    }
                    
                    else
                    {
                        if(isdigit(stream[i+1]))
                        {
                            for(int l = 0;l<2; l++)
                            {
                                ret[j] = stream[i];
                                j++;
                                i++;
                            }
                            while(isdigit(stream[i]))
                            {
                                ret[j] = stream[i];
                                i++;
                                j++;
                            }
                            
                            tk->cursor = i;
                            
                            printf("float ");
                            return ret;
                            
                        }
                        
                        else
                        {
                            for(int l = 0; l<2; l++)
                            {
                                ret[j] = stream[i];
                                j++;
                                i++;
                            }
                            
                            tk->cursor = i;
                            
                            printf("error malformed input: ");
                            return ret;
                        }
                        
                    }
                    
                }

                
                if (stream[i]== '.')
                {
                    if(isdigit(stream[i+1]))
                    {
                        for(int k = 0; k<2; k++)
                        {
                            ret[j] = stream[i];
                            j++;
                            i++;
                        }
                        while(isdigit(stream[i]))
                        {
                            ret[j] = stream[i];
                            i++;
                            j++;
                        }
                        
                        if(stream[i] == 'E' || stream[i] == 'e')
                        {
                            if(stream[i+1] == '+' || stream[i+1] == '-')
                            {
                                
                                if(isdigit(stream[i+2]))
                                {
                                    for(int l = 0; l<2; l++)
                                    {
                                        ret[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    
                                    
                                    while(isdigit(stream[i]))
                                    {
                                        ret[j] = stream[i];
                                        i++;
                                        j++;
                                    }
                                    
                                    tk->cursor = i;
                                    
                                    printf("float ");
                                    return ret;
                                    
                                }
                                
                                else
                                {
                                    for(int l = 0; l<3; l++)
                                    {
                                        ret[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    
                                    tk->cursor = i;
                                    
                                    printf("error malformed input: ");
                                    return ret;
                                }
                            }
                            
                            else
                            {
                                if(isdigit(stream[i+1]))
                                {
                                    for(int l = 0;l<2; l++)
                                    {
                                        ret[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    while(isdigit(stream[i]))
                                    {
                                        ret[j] = stream[i];
                                        i++;
                                        j++;
                                    }
                                    
                                    tk->cursor = i;
                                    
                                    printf("float ");
                                    return ret;
                                    
                                }
                                
                                else
                                {
                                    for(int l = 0; l<2; l++)
                                    {
                                        ret[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    
                                    tk->cursor = i;
                                    
                                    printf("error malformed input: ");
                                    return ret;
                                }
                                
                            }
                            
                        }
                        
                        tk->cursor = i;
                        
                        printf("float ");
                        return ret;
                    }
                }

            }
            
            tk->cursor = i;
            
            printf("decimal ");
            return ret;
            
        }
        
    }
    if(stream[i] == '.')
    {
        printf("period ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
    }
    
    if(stream[i] == '(')
    {
        printf("leftparentheses ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
    }
    
    if(stream[i] == ')')
    {
        printf("rightparetheses ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
    }
    
    if(stream[i] == '{')
    {
        printf("leftbracket ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
    }
    
    if(stream[i] == '}')
    {
        printf("rightbracket ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '[')
    {
        printf("leftbrace ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == ']')
    {
        printf("rightbrace ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i]== '+')
    {
        if(stream[i+1] == '=')
        {
            printf("plusequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
        }
        if(stream[i+1] == '+')
        {
            printf("increment ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
        }
        printf("plus ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i]== '-')
    {
        if(stream[i+1] == '=')
        {
            printf("minusequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '-')
        {
            printf("decrement ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '>')
        {
            printf("structurepointer ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("minus ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '*')
    {
        if(stream[i+1] == '=')
        {
            printf("multiplyequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
        }
        printf("multiply ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '*')
    {
        if(stream[i+1] == '=')
        {
            printf("divideequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("divide ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '%')
    {
        if(stream[i+1] == '=')
        {
            printf("modulusequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("modulus ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '&')
    {
        if(stream[i+1] == '&')
        {
            printf("logicaland ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '=')
        {
            printf("andor ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("and ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '!')
    {
        if(stream[i+1] == '=')
        {
            printf("notequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("negate ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '~')
    {
        printf("1'scomp ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i]== '<')
    {
        if(stream[i+1] == '=')
        {
            printf("lessorequal ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '<')
        {
            printf("shiftleft ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("lessthan ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '>')
    {
        if(stream[i+1] == '=')
        {
            printf("greaterorequal ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '>')
        {
            printf("shiftright ");
            
        }
        printf("greaterthan ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '^')
    {
        if(stream[i+1] == '=')
        {
            printf("exclusiveorequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("exclusiveor ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '|')
    {
        if(stream[i+1] == '|')
        {
            printf("logicalor ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        if(stream[i+1] == '=')
        {
            printf("orequals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("bitwiseor ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i]== ':')
    {
        printf("colon ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == ';')
    {
        printf("semicolon ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i]== '=')
    {
        if(stream[i+1] == '=')
        {
            printf("equals ");
            while(j<2)
            {
                ret[j] = stream[i];
                j++;
                i++;
            }
            tk->cursor = i;
            return ret;
            
        }
        printf("assignment ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    
    if(stream[i] == '\\')
    {
        printf("backslash ");
        ret[j] = stream[i];
        j++;
        i++;
        tk->cursor = i;
        return ret;
        
    }
    else if((stream[i-1] == ' ' || stream[i-1] == '\t' || stream[i-1] == '\v' || stream[i-1] == '\t' || stream[i-1] == '\f' || stream[i-1] == '\r' || stream[i-1] == '\n') && i == tk->strLength )
    {
        tk->error = 1;
        ret[j] = '\0';
        tk->cursor = i;
        return ret;
        
    }
    
    else
    {
        tk->error = 1;
        printf("error: [Ox%02x]\n", stream[i]);
        ret[j] = '\0';
        i++;
        tk->cursor = i;
        return ret;
        
    }

    i++;
    
    return "bugz";
    
    
    
}

/*
 * main will have stream[i]string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on stream[i]separate line.
 */

int main(int argc, char **argv) {
    
    if (argc == 1)
    {
        printf("error: did not enter a string\n");
        return 0;
    }
    
    if (argc != 2)
    {
        printf("error: too many arguments\n");
        return 0;
    }
    
    char* str = argv[1];
    TokenizerT* tokenizer = TKCreate(str);
    
    while (tokenizer->cursor<(tokenizer->strLength))
    {
    tokenizer->curr = TKGetNextToken(tokenizer);
        if(tokenizer->error == 1)
        {
            tokenizer->error = 0;
            continue;
        }
        
        printf("\"%s\"\n", tokenizer->curr);
    }
    
    TKDestroy(tokenizer);
    
    return 0;
}


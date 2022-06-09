/**
 * @defgroup   DIFFERENTIATOR Differentiator
 *
 * @brief      This file implements Differentiator.
 *
 * @author     Stas
 * @date       2021
 */


#include "Differentiator.h"


Node_t* Differentiator_Differentiate(Node_t* NODE)
{
	if (!NODE)
	{
		Logger_message("Warning! nullptr in Differentiator_Differentiate()");

		return nullptr;
	}

	Node_t* derivative = nullptr;
	
	switch (NODE->type) 
	{
		case TYPE_NAMED_CONST: derivative = NEW_CONST(0); break;

		case TYPE_CONST: 	   derivative = NEW_CONST(0); break;

		case TYPE_VAR:   	   derivative = NEW_CONST(1); break;

		case TYPE_OP:    	   derivative = Differentiator_DifferentiateOperation(NODE); break;

		case TYPE_FUNC:  	   derivative = Differentiator_DifferentiateFunction (NODE); break;

		default: 

			Logger_message("Invalid token type"); 

			derivative = nullptr;
	}

	Differentiator_PrintRandomPhrase();

	printf("(");

	Differentiator_ShowResult(stdout, NODE);

	printf(")' = ");

	Differentiator_ShowResult(stdout, derivative);

	printf("\n\n");

	return derivative;
}


Node_t* Differentiator_DifferentiateOperation(Node_t* NODE)
{
	Logger_assert(NODE && "Current node pointer is NULL in Differentiator_DifferentiateOperation()");

	switch (NODE->value)
	{
		case OP_ADD: return ADD(D(L), D(R));

		case OP_SUB: return SUB(D(L), D(R));

		case OP_MUL: return ADD(MUL(D(L), NEW_R), MUL(NEW_L, D(R)));

		case OP_DIV: return DIV(SUB(MUL(D(L), NEW_R), MUL(NEW_L, D(R))), POW(NEW_R, NEW_CONST(2)));

		case OP_POW: 

			if      (IS_CONST(L) && (IS_OP(R) || IS_VAR(R)))  return MUL(MUL(POW(NEW_L, NEW_R), LN(NEW_L)), D(R));
			
			else if (IS_CONST(L) && IS_CONST(R)) 			  return NEW_CONST(0);

			else if ((IS_OP(L) || IS_VAR(L)) && IS_CONST(R))  return MUL(MUL(NEW_R, POW(NEW_L, NEW_CONST(RVALUE - 1))), D(L));

			else                                              return MUL(POW(NEW_NAMED_CONST(E_CONST), MUL(NEW_R, LN(NEW_L))), 

																	 ADD(MUL(D(R), LN(NEW_L)), MUL(NEW_R, MUL(D(L), DIV(NEW_CONST(1), NEW_L)))));

		default: 

			Logger_message("Invalid operation"); 

			return nullptr;
	}

	return nullptr;
}


Node_t* Differentiator_DifferentiateFunction(Node_t* NODE)
{
	Logger_assert(NODE && "Current node pointer is NULL in Differentiator_DifferentiateFunction()");

	switch (NODE->value)
	{

		case OP_SIN: 	return MUL(COS(NEW_L), D(L));

		case OP_COS: 	return MUL(SUB(NULL, SIN(NEW_L)), D(L));

		case OP_TG:  	return MUL(DIV(NEW_CONST(1), POW(COS(NEW_L), NEW_CONST(2))), D(L));

		case OP_CTG: 	return MUL(DIV(SUB(NULL, NEW_CONST(1)), POW(SIN(NEW_L), NEW_CONST(2))), D(L));

		case OP_LOG: 	return MUL(MUL(DIV(NEW_CONST(1), NEW_R), DIV(NEW_CONST(1), LN(NEW_L))), D(R));

		case OP_LN:  	return MUL(DIV(NEW_CONST(1), NEW_L), D(L));

		case OP_ARCTG:  return MUL(DIV(NEW_CONST(1), ADD(NEW_CONST(1), POW(NEW_VAR(X_VAR), NEW_CONST(2)))), D(L));

		case OP_ARCCTG: return MUL(SUB(NULL, D(ARCTG(L))), D(L));

		case OP_ARCSIN: return MUL(DIV(NEW_CONST(1), POW(SUB(NEW_CONST(1), POW(NEW_VAR(X_VAR), NEW_CONST(2))), DIV(NEW_CONST(1), NEW_CONST(2)))), D(L));

		case OP_ARCCOS: return MUL(SUB(NULL, D(ARCSIN(L))), D(L));

		case OP_SH:     return MUL(CH(L), D(L));

		case OP_CH:     return MUL(SH(L), D(L));

		case OP_TH:     return MUL(DIV(NEW_CONST(1), POW(CH(L), NEW_CONST(2))), D(L));

		case OP_CTH:    return MUL(SUB(NULL, DIV(NEW_CONST(1), POW(SH(L), NEW_CONST(2)))), D(L));

		default: 

			Logger_message("Invalid function"); 

			return nullptr;
	}

	return nullptr;
}


Node_t* Differentiator_NewNode(NodeType_t nodeType, NodeValue_t nodeValue, Node_t* nodeLeft, Node_t* nodeRight)
{
	Node_t* newNode = (Node_t*) calloc(1, sizeof (Node_t));

	if (newNode == nullptr)
	{
		Logger_message("Allocation error");
		return nullptr;
	}

	newNode->type  = nodeType;
	newNode->value = nodeValue;

	newNode->left  = nodeLeft;
	newNode->right = nodeRight;

	return newNode;
}


Node_t* Differentiator_CreateNewSubTree(Node_t* node)
{
	Logger_assert(node && "Node pointer is NULL in Differentiator_CreateNewSubTree()");

	Node_t* newNode = Differentiator_NewNode(node->type, node->value, NULL, NULL);

	if (node->left)
	{
		newNode->left = Differentiator_CreateNewSubTree(node->left);
	}

	if (node->right)
	{
		newNode->right = Differentiator_CreateNewSubTree(node->right);
	}

	return newNode;
}


Tree_t* Differentiator_CreateTree(char* expression)
{
	Logger_assert(expression && "Expression pointer is NULL in CreateTree()");

	Tree_t* expressionTree = (Tree_t*) calloc(1, sizeof (Tree_t));

	if (!expressionTree)
	{
		Logger_message("Allocation error");

		return NULL; 	
 	}

	Differentiator_SkipWhiteSpaces(&expression);

 	expressionTree->root = Differentiator_GetGrammar(expression);

 	return expressionTree;
}


Node_t* Differentiator_GetGrammar(const char* expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetGrammar()");

	Node_t* value = Differentiator_GetExpression(&expression);

	return value;
}


Node_t* Differentiator_GetExpression(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetExpression()");

	Node_t* value = Differentiator_GetMultiplication(expression);

	while (**expression == '+' || **expression == '-')
	{
		int operation = **expression;
		NEXT;

		Node_t* value2 = Differentiator_GetMultiplication(expression);

		if      (operation == '+') value = ADD(value, value2);
		else if (operation == '-') value = SUB(value, value2);
	}

	return value;
}


Node_t* Differentiator_GetMultiplication(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetMultiplication()");

	Node_t* value = Differentiator_GetPower(expression);

	while (**expression == '*' || **expression == '/')
	{
		int operation = **expression;
		NEXT;

		Node_t* value2 = Differentiator_GetPower(expression);

		if      (operation == '*') value = MUL(value, value2);
		else if (operation == '/') value = DIV(value, value2);
	}

	return value;
}


Node_t* Differentiator_GetPower(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetPower()");

	Node_t* value = Differentiator_GetBrackets(expression);

	while (**expression == '^')
	{
		NEXT;

		Node_t* value2 = Differentiator_GetBrackets(expression);

		value = POW(value, value2);
	}

	return value;
}


#define DEF_FUNC(operation, opValue, name) 							\
																	\
else if (strncmp(name, *expression, strlen(name)) == 0) 			\
{																	\
	value = Differentiator_GetFunction(expression, name, opValue);	\
}


Node_t* Differentiator_GetBrackets(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetBrackets()");

	Node_t* value = NULL;

	int coefficient = Differentiator_GetUnarySign(expression);

	if (**expression == '(')
	{
		REQUIRE('(');

		value = Differentiator_GetExpression(expression);

		REQUIRE(')');
	}

	else if (**expression >= '0' && **expression <= '9')
	{
		value = Differentiator_GetNumber(expression);
	}

	#include "Functions.h"

	#undef DEF_FUNC

	else
	{
		value = Differentiator_GetVariable(expression);
	}

	return Differentiator_CreateNodeWithCoefficient(value, coefficient);
}


Node_t* Differentiator_GetFunction(const char** expression, const char* functionName, NodeValue_t functionValue)
{
	Logger_assert(expression   &&    "Expression pointer is NULL in Differentiator_GetFunction()");
	Logger_assert(functionName && "Function name pointer is NULL in Differentiator_GetFunction()");

	*expression += strlen(functionName);

	Node_t* value  = NULL;
	Node_t* value2 = NULL;

	REQUIRE('('); 

	value = Differentiator_GetExpression(expression);

	REQUIRE(')');

	if (strncmp(functionName, "log", strlen(functionName)) == 0)
	{
		REQUIRE('('); 

		value2 = Differentiator_GetExpression(expression);

		REQUIRE(')');
	}

	return NEW_FUNC(functionValue, value, value2);
}


Node_t* Differentiator_GetVariable(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetVariable()");

	const char* oldptr = *expression;

	Node_t* value = NULL;

	if (**expression == 'x')
	{
		NEXT;
		value = NEW_VAR(X_VAR);
	}

	if (*expression == oldptr)
	{
		Logger_message("Syntax error");

		return NULL;
	}

	return value;
}


Node_t* Differentiator_GetNumber(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetNumber()");

	const char* oldptr = *expression;

	int value = 0;

	while (**expression >= '0' && **expression <= '9')
	{
		value = value * 10 + (**expression - '0');
		NEXT;
	}

	if (*expression == oldptr)
	{
		Logger_message("Syntax error");

		return NULL;
	}

	return NEW_CONST(value);
}


int Differentiator_GetUnarySign(const char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_GetUnarySign()");

	int coefficient = 1;

	if (**expression == '-')
	{
		coefficient = -1;
		NEXT;
	}

	else if (**expression == '+')
	{
		coefficient = 1;
		NEXT;
	}

	return coefficient;
}


Node_t* Differentiator_CreateNodeWithCoefficient(Node_t* node, int coefficient)
{
	Logger_assert(node && "Node pointer is NULL in Differentiator_CreateNodeWithCoefficient()");

	if (coefficient == -1)
	{
		return SUB(NULL, node);
	}

	else if (coefficient == 1)
	{
		return node;
	}

	return NULL;
}


int Differentiator_SkipWhiteSpaces(char** expression)
{
	Logger_assert(expression && "Expression pointer is NULL in Differentiator_SkipWhiteSpaces()");

	int leftFinger  = 0;
	int rightFinger = 0;

	while ((*expression)[rightFinger] != '\0')
	{
		if (isspace((*expression)[rightFinger]))
		{
			rightFinger += 1;
		}

		else
		{
			(*expression)[leftFinger] = (*expression)[rightFinger];

			leftFinger  += 1;
			rightFinger += 1;
		}
	}

	(*expression)[leftFinger] = '\0';

	return rightFinger - leftFinger; // hand
}


Node_t* Differentiator_HigherOrderDerivative(Node_t* startNode, int order)
{
	Logger_assert(startNode && "Start node pointer is NULL in Differentiator_HigherOrderDerivative()");

	Node_t* currentDerivative = startNode;

	while (order)
	{
		currentDerivative = Differentiator_Differentiate(currentDerivative);

		order -= 1;
	}

	return currentDerivative;
}


Node_t* Differentiator_Simplify(Node_t* startNode)
{
	Logger_assert(startNode && "Start node pointer is NULL Differentiator_Simplify()");

	Differentiator_ZeroMultiplication(startNode);

	Differentiator_MultiplicationByOne(startNode);

	Differentiator_EmptyNodes(startNode);

	// Differentiator_ConsecutiveOperations(startNode);

	return startNode;
}


bool Differentiator_MultiplicationByOne(Node_t* NODE)
{
	Logger_assert(NODE && "NODE pointer is NULL in Differentiator_MultiplicationByOne()");

	if (IS_OP(NODE) && VALUE == OP_MUL)
	{
		if (L)
		{
			if (IS_CONST(L) && LVALUE == 1)
			{
				DifferentiatorTree_NodeDtor(NODE);
				
				return true;
			}
		}

		if (R)
		{
			if (IS_CONST(R) && RVALUE == 1)
			{
				DifferentiatorTree_NodeDtor(NODE);

				return true;
			}
		}
	}

	if (L)
	{
		if (Differentiator_ZeroMultiplication(L)) L = NULL;
	}

	if (R)
	{
		if (Differentiator_ZeroMultiplication(R)) R = NULL;
	}

	return false;
}


bool Differentiator_ZeroMultiplication(Node_t* NODE)
{
	Logger_assert(NODE && "Start node pointer is NULL in Differentiator_ZeroMultiplication()");

	if (IS_OP(NODE) && VALUE == OP_MUL)
	{
		if (L)
		{
			if (IS_CONST(L) && LVALUE == 0)
			{
				DifferentiatorTree_NodeDtor(NODE);
				
				return true;
			}
		}

		if (R)
		{
			if (IS_CONST(R) && RVALUE == 0)
			{
				DifferentiatorTree_NodeDtor(NODE);

				return true;
			}
		}
	}

	if (L)
	{
		if (Differentiator_ZeroMultiplication(L)) L = NULL;
	}

	if (R)
	{
		if (Differentiator_ZeroMultiplication(R)) R = NULL;
	}

	return false;
}


bool Differentiator_EmptyNodes(Node_t* NODE)
{
	Logger_assert(NODE && "Current node pointer is NULL in Differentiator_EmptyNodes()");

	if (L)
	{
		if (Differentiator_EmptyNodes(L)) L = NULL;
	}

	if (R)
	{
		if (Differentiator_EmptyNodes(R)) R = NULL;
	}

	if (!L && !R && IS_OP(NODE))
	{
		DifferentiatorTree_NodeDtor(NODE);

		return true;
	}

	return false;
}


bool Differentiator_ConsecutiveOperations(Node_t* NODE)
{
	Logger_assert(NODE && "Current node pointer is NULL in Differentiator_ConsecutiveOperations()");

	if (L) Differentiator_ConsecutiveOperations(L);

	if (R) Differentiator_ConsecutiveOperations(R);

	if (IS_OP(NODE) && VALUE == OP_ADD)
	{
		if (!R && L && IS_OP(L) && LVALUE == OP_ADD)
		{
			if (L->left)  L = Differentiator_CreateNewSubTree(L->left);
			if (L->right) R = Differentiator_CreateNewSubTree(L->right);

			DifferentiatorTree_NodeDtor(L);

			return true;
		}

		else if (R && !L && IS_OP(R) && RVALUE == OP_ADD)
		{
			if (R->left)  L = Differentiator_CreateNewSubTree(R->left);
			if (R->right) R = Differentiator_CreateNewSubTree(R->right);

			DifferentiatorTree_NodeDtor(R);

			return true;
		}
	}

	return false;
}


int Differentiator_GetOrder(Node_t* node)
{
	Logger_assert(node && "Node pointer  is NULL in Differentiator_GetOrder()");

	if (node->type != TYPE_OP)
	{
		return -1u;
	}

	if (node->value == OP_POW)
	{
		return 3;
	}

	if (node->value == OP_MUL || node->value == OP_DIV)
	{
		return 2;
	}

	if (node->value == OP_ADD || node->value == OP_SUB)
	{
		return 1;
	}

	return -1;
}


Node_t* Differentiator_TaylorExpansion(Node_t* function, int order, int point)
{
	Logger_assert(function && "Function pointer is NULL in Differentiator_TaylorExpansion()");

	Node_t* expansion = NEW_CONST(0);

	Node_t* currentDerivative = function;

	for (int i = 0; i < order; ++i)
	{
		expansion = ADD(MUL(DIV(NEW_NODE(IN_POINT(currentDerivative)), NEW_CONST(i)), POW(SUB(NEW_VAR(X_VAR), NEW_CONST(point)), NEW_CONST(i))), expansion);

		// DifferentiatorTree_DumpTree(expansion);

		currentDerivative = D(currentDerivative);
	}

	expansion= Differentiator_Simplify(expansion);

	Differentiator_ShowResult(stdout, expansion);
	
	return expansion;
}


Node_t* Differentiator_ReplaceVariable(Node_t* NODE, int point)
{
	Logger_assert(NODE && "NODE pointer is NULL in Differentiator_ReplaceVariable()");

	if (IS_VAR(NODE))
	{
		VALUE = point;

		NODE->type = TYPE_CONST;
	}

	if (L)
	{
		Differentiator_ReplaceVariable(L, point);
	}

	if (R)
	{
		Differentiator_ReplaceVariable(R, point);
	}

	return NODE;
}


void Differentiator_DumpToTex(FILE* destFile, Node_t* NODE)
{
	Logger_assert(destFile && "Destination file pointer is NULL in Differentiator_DumpToTex()");
	Logger_assert(NODE     &&             "NODE pointer is NULL in Differentiator_DumpToTex()");

	fprintf(destFile, "\\documentclass{article}\n"
					  "\\usepackage[utf8]{inputenc}\n"
					  "\\usepackage[T2A]{fontenc}\n"
					  "\\usepackage[russian]{babel}\n"
					  "\\usepackage{amssymb}\n"
					  "\\usepackage{amsmath}\n"
					  "\\usepackage[normalem]{ulem}\n"
					  "\\usepackage[left=25mm, top=10mm, right=10mm, bottom=10mm, nohead, nofoot]{geometry}\n"
					  "\\begin{document}\n");

	fprintf(destFile, "$\n");

	Differentiator_ShowResult(destFile, NODE);

	fprintf(destFile, "$\n");

	fprintf(destFile, "\\end{document\n");
}


DIFFERENTIATOR_ERRORS Differentiator_ShowResult(FILE* destFile, Node_t* NODE)
{
	Logger_assert(NODE && "Current node pointer is NULL in Differentiator_ShowResult(stdout, )");

	if (IS_OP(NODE))
	{
		if (VALUE == OP_ADD)
		{
			if (L && !R) {Differentiator_ShowResult(stdout, L); return DIF_NO_ERROR;}
			if (R && !L) {Differentiator_ShowResult(stdout, R); return DIF_NO_ERROR;}
		}

		if (VALUE == OP_SUB && !L && R)
		{
			fprintf(destFile, "-");

			Differentiator_ShowResult(stdout, R);

			return DIF_NO_ERROR;
		}

		if (L)
		{
			if (IS_OP(L) && Differentiator_GetOrder(L) < Differentiator_GetOrder(NODE))
			{
				fprintf(destFile, "{(");

				Differentiator_ShowResult(stdout, L);
				
				fprintf(destFile, ")}");
			}

			else
			{
				Differentiator_ShowResult(stdout, L);
			}
		}

		Differentiator_PrintNode(NODE);

		if (R)
		{
			if (IS_OP(R) && Differentiator_GetOrder(R) < Differentiator_GetOrder(NODE))
			{
				fprintf(destFile, "{(");
				
				Differentiator_ShowResult(stdout, R);
				
				fprintf(destFile, ")}");
			}

			else
			{
				Differentiator_ShowResult(stdout, R);
			}
		}
	}

	else if (IS_FUNC(NODE))
	{
		Differentiator_PrintNode(NODE);

		if (L)
		{
			fprintf(destFile, "{(");

			Differentiator_ShowResult(stdout, L);
		
			fprintf(destFile, ")}");
		}

		if (R)
		{
			fprintf(destFile, "{(");

			Differentiator_ShowResult(stdout, R);
		
			fprintf(destFile,")}");
		}
	}

	else
	{
		Differentiator_PrintNode(NODE);
	}

	return DIF_NO_ERROR;
}


Node_t* Differentiator_PrintNode(Node_t* NODE)
{
	Logger_assert(NODE && "Node pointer is NULL in Differentiator_PrintNode()");

	switch (NODE->type)
	{
		case TYPE_VAR:
		{
			printf("%c", (char) NODE->value);
		
			break;
		}

		case TYPE_OP:
		{
			printf("%c", (char) NODE->value);

			break;			
		}

		case TYPE_CONST:
		{

			printf("%llu", NODE->value);

			break;
		}

		case TYPE_NAMED_CONST:
		{
			printf("%c", (char) NODE->value);

			break;
		}

		case TYPE_FUNC:
		{
			NodeValue_t currentValue = NODE->value;

			printf("\\%c", (char) (currentValue % 1000));
			
			currentValue /= 1000;
			
			while (currentValue > 0)
			{
				printf("%c", (char) (currentValue % 1000));
			
				currentValue /= 1000;
			}

			printf("{");

			break;
		}

		default: Logger_message("Something went wring in Differentiator_PrintNode()");
	}

	return NODE;
}


int Differentiator_PrintRandomPhrase()
{
	const char* phrases[NUMBER_OF_PHRASES] = {

		"Obviously\n",
		"Yesterday I ate, today it's time to differentiate\n",
		"It will be a miracle if I calculate this right\n",
		"Death or math\n",
		"Do you enjoy differentiating, boy?\n",
		"Use only infinitive when calculating this derivative\n",
		"This derivative is so primitive!\n",
		"I lost all the initiative while calculating this derivative\n",
		"This Differentiator is a freaking Terminator\n",
		"Let's put some acceleration to this differentiation\n",
		"I'll get some beer from refrigerator while you're working on this, Differentiator\n",
		"This differentiation is a pure discrimination\n",
		"What kind of gay party is this?\n",
		"I'm becoming a hater of this Differentiator\n",
		"My Differentiator couldn't be any greater\n"
	};             											// ~ внешная рифма ~

	int randPhrase = (int) rand();

	printf("%s", phrases[randPhrase % NUMBER_OF_PHRASES]);

	return randPhrase;
}

/* 
 * Recursive descent parse for p1 grammar
 * @author Tom Hadlaw.
 * @version 1.0.0
 */
public class rdparse
{
	public final static int PARSE_SUCCESS = 1;
	public final static int PARSE_FAILURE = 0;

	private String current;
	private String tokens[];
	private int index = 0;

	/* 
	 * Declaration function.
	 * @param in String array of all tokens (case sensitive).
     * note all tokens must be in seperate array strings
     * (ex: [:][=] not [:=] in this case)
	 */
	public rdparse(String in[])
	{
		tokens = in;
		current = tokens[0];
	}
	
	/* makes current the next String in the token array */
	private void next()
	{
		index++;
		current = tokens[index];
	}

	/* program nonterminal */
	private void parse_Program()
	{
		if (current.equals("begin"))
		{
			next();		
			parse_StatementList();
			if (current.equals("end")) 
			{
				if (index == tokens.length - 1)
				{
					System.out.println("No eof symbol ($)");
				}
				else next();
			}
		}
	}

	/* statement list nonterminal */	
	private void parse_StatementList()
	{
		parse_Statement();
		parse_StatementTail();
	}

	/* statement tail nonterminal */
	private void parse_StatementTail()
	{
		if (current.equals("Id") || current.equals("read") ||
				current.equals("write"))
		{
			parse_Statement();
			parse_StatementTail();
		}
		else next();
	}

	/* parse statement nonterminal */	
	private void parse_Statement()
	{
		if (current.equals("Id"))
		{
			next();
			if (current.equals(":"))
			{
				next();
				if (current.equals("=")) parse_Expression();
				next();
				if (current.equals(";")) next();
			}
		}

		if (current.equals("read"))
		{
			next();
			if (current.equals("("))
			{
				next();
				parse_IdList();
				if (current.equals(")"))
				{
					next();
					if (current.equals(";")) next();
				}
			}
		}

		if (current.equals("write"))
		{
			next();
			if (current.equals("("))
			{
				parse_ExprList();
				next();
				if (current.equals(")"))
				{
					next();
					if (current.equals(";")) next();
				}
			}
		}
			
	}

	/* idlist nonterminal */	
	private void parse_IdList()
	{
		if (current.equals("Id"))
		{
			next();
			parse_IdTail();
		}
	}

	/* id tail nonterminal */
	private void parse_IdTail()
	{
		if (current.equals(","))
		{
			next();
			if (current.equals("Id"))
			{
				next();
				parse_IdTail();
			}
		}
		else next();		
	}

	/* expr list nonterminal */
	private void parse_ExprList()
	{
		parse_Expression();
		parse_ExprTail();
	}

	/* expr tail nonterminal */
	private void parse_ExprTail()
	{
		if (current.equals(","))
		{
			parse_Expression();
			parse_ExprTail();
		}
		else next();
	}

	/* expression nonterminal */
	private void parse_Expression()
	{
		parse_Primary();
		parse_PrimaryTail();
	}

	/* primary tail nonterminal */
	private void parse_PrimaryTail()
	{
		if (current.equals("("))
		{
			next();
			parse_Expression();
			if (current.equals(")")) next();
		}
		else if (current.equals("+") || current.equals("-"))
		{
			parse_AddOp();
			parse_Primary();
			parse_PrimaryTail();
		}
		else next();
	}

	/* primary nonterminal */
	private void parse_Primary()
	{
		if (current.equals("Id")) next();
		else if (current.equals("INTLIT"));	
	}

	/* addop nonterminal */
	private void parse_AddOp()
	{
		if (current.equals("+")) next();
		else if (current.equals("-"));
	}

	/* SystemGoal nonterminal */
	private int parse_SystemGoal()
	{
		parse_Program();
		if (current.equals("$"))
		{
			return PARSE_SUCCESS;
		}
		return PARSE_FAILURE;
	}
	/*
	 * Parses the token array.
	 * @return 1 if success 0 otherwise.
	 */
	public int parse()
	{
		if (tokens.length == 0)
		{
			System.out.println("empty input");
			return 0;
		}
		else 
		{
			int ret = parse_SystemGoal();
			if (ret == PARSE_SUCCESS 
				&& index == tokens.length -1)
			{
				System.out.println("Parse successful");
				return PARSE_SUCCESS;
			}
			else
			{
				System.out.println("Parse unsuccesful") ;
				System.out.println("Token: '" + tokens[index] + 
					"' could not be matched");
				return PARSE_FAILURE;
			}
		}
	}
}


#include "bruter-representation.h"

BruterList*   br_default_parser(BruterList *context); 
BruterList*   br_default_evaluator(BruterList *context);

// default-lang parser steps declarations
BR_PARSER_STEP(parser_char);
BR_PARSER_STEP(parser_string);
BR_PARSER_STEP(parser_number);
BR_PARSER_STEP(parser_list);
BR_PARSER_STEP(parser_function_arg);
BR_PARSER_STEP(parser_function);
BR_PARSER_STEP(parser_variable);
BR_PARSER_STEP(parser_conditional);
BR_PARSER_STEP(parser_spread);
BR_PARSER_STEP(parser_comment);
BR_PARSER_STEP(parser_expression);
BR_PARSER_STEP(parser_attr);
BR_PARSER_STEP(parser_attr_get);
BR_PARSER_STEP(parser_reuse);

// default-lang evaluation steps declarations
BR_EVALUATOR_STEP(eval_step_function);
BR_EVALUATOR_STEP(eval_step_buffer);
BR_EVALUATOR_STEP(eval_step_list);
BR_EVALUATOR_STEP(eval_step_baked);
BR_EVALUATOR_STEP(eval_step_user_function);

// parsing steps
// parsing steps
// parsing steps
// parsing steps
// parsing steps
// parsing steps
// parsing steps
BR_PARSER_STEP(parser_char)
{
    BR_PARSER_STEP_BASICS();
    if (current_word[0] == '\'' && current_word[2] == '\'')
    {
        BruterInt index = br_new_var(context, (BruterValue){.i = current_word[1]}, NULL, BR_TYPE_ANY);
        bruter_push(result, (BruterValue){.i = index}, NULL, 0);
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_list)
{
    BR_PARSER_STEP_BASICS();
    if (current_word[0] == '[') // its a list
    {
        BruterList *list = NULL;
        BruterInt index = -1;
        current_word[strlen(current_word) - 1] = '\0'; // remove the closing parenthesis
        list = br_parse(context, br_get_parser(context), current_word + 1); // parse the list
        index = br_new_var(context, (BruterValue){.p=(void*)list}, NULL, BR_TYPE_LIST);
        bruter_push(result, (BruterValue){.i = index}, NULL, 0);
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_expression)
{
    BR_PARSER_STEP_BASICS();
    if (current_word[0] == '(')
    {
        char* temp = current_word + 1;
        BruterInt res = -1;
        temp[strlen(temp) - 1] = '\0';
        res = br_eval(context, temp);
        bruter_push(result, (BruterValue){.i = res}, NULL, 0);
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_string)
{
    BR_PARSER_STEP_BASICS();
    if (current_word[0] == '{')
    {
        BruterInt index = -1;
        char* new_str = br_str_nduplicate(current_word + 1, strlen(current_word) - 2);
        index = br_new_var(context, (BruterValue){.p=(void*)new_str}, NULL, BR_TYPE_BUFFER);
        bruter_push(result, (BruterValue){.i = index}, NULL, 0);
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_number)
{
    BR_PARSER_STEP_BASICS();
    if ((current_word[0] >= '0' && current_word[0] <= '9') || (current_word[0] == '-' && isdigit(current_word[1]))) // number
    {
        BruterInt index = br_new_var(context, (BruterValue){.p=NULL}, NULL, 0);
        
        if (current_word[0] == '0' && current_word[1] == 'x') // hex
        {
            context->data[index].i = strtol(current_word+2, NULL, 16);
            context->types[index] = BR_TYPE_ANY;
        }
        else if (current_word[0] == '0' && current_word[1] == 'b') // bin
        {
            context->data[index].i = strtol(current_word+2, NULL, 2);
            context->types[index] = BR_TYPE_ANY;
            
        }
        else if (current_word[0] == '0' && current_word[1] == 'o') // oct
        {
            context->data[index].i = strtol(current_word+2, NULL, 8);
            context->types[index] = BR_TYPE_ANY;
        }
        else if (strchr(current_word, '.')) // float
        {
            context->data[index].f = atof(current_word);
            context->types[index] = BR_TYPE_FLOAT;
        }
        else // int
        {
            context->data[index].i = atol(current_word);
            context->types[index] = BR_TYPE_ANY;
        }

        bruter_push_int(result, index, NULL, 0);
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_attr)
{
    BR_PARSER_STEP_BASICS();
    // attributes
    if (current_word[0] == '.')
    {
        if (result->size <= 0)
        {
            printf("result size: %" PRIdPTR ", but we need at least 1 element\n", result->size);
            printf("BR_ERROR: %s has no previous value\n", current_word);
        }
        else if (result->data[result->size - 1].i == -1)
        {
            printf("BR_ERROR: %s previous value is not a variable\n", current_word);
        }
        // we need to verify if there is a next word yet to parse
        else if (word_index + 1 >= splited_command->size)
        {
            printf("BR_ERROR: %s attribute requires a name to be set\n", current_word);
            return true;
        }
        else // default behavior
        {
            // we need to name the last value from the result
            BruterInt last_index = result->data[result->size - 1].i;
            
            if (last_index < 0 || last_index >= context->size)
            {
                printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                return true;
            }
            
            // we need to get the next word from the splited command
            char* next_word = ((char*)bruter_remove_pointer(splited_command, word_index + 1));

            // name attribute
            if (strcmp(current_word + 1, "name") == 0)
            {
                context->keys[last_index] = br_str_duplicate(next_word); // set the key to the last value
                printf("BR_DEBUG: setting key %s to %s\n", context->keys[last_index], next_word + 1);
            }
            else if (strcmp(current_word + 1, "type") == 0) 
            {
                context->types[last_index] = (int8_t)atoi(next_word); // set the type to the last value
            }

            free(next_word);
        }
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_attr_get)
{
    BR_PARSER_STEP_BASICS();
    // attributes
    if (current_word[0] == ':')
    {
        if (unlikely(result->size <= 0))
        {
            printf("result size: %" PRIdPTR ", but we need at least 1 element\n", result->size);
            printf("BR_ERROR: %s has no previous value\n", current_word);
        }
        else if (unlikely(result->data[result->size - 1].i == -1))
        {
            printf("BR_ERROR: %s previous value is not a variable\n", current_word);
        }
        else if (current_word[1] ==  '\0') // invalid
        {
            printf("BR_ERROR: : alone is not valid\n");
        }
        else // default behavior
        {
            if (strcmp(current_word + 1, "name") == 0) // name attribute
            {
                // we need to get the last value from the result
                BruterInt last_index = bruter_pop_int(result);
                
                if (last_index < 0 || last_index >= context->size)
                {
                    printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                    return true;
                }
                
                // we need to create a new value with the key of the last value
                char* key = context->keys[last_index];
                if (key == NULL)
                {
                    printf("BR_ERROR: %s has no key\n", current_word);
                    return true;
                }
                BruterInt index = br_new_var(context, (BruterValue){.p=(void*)key}, NULL, BR_TYPE_BUFFER);
                bruter_push(result, (BruterValue){.i = index}, NULL, 0);
            }
            else if (strcmp(current_word + 1, "type") == 0) // type attribute
            {
                // we need to get the last value from the result
                BruterInt last_index = bruter_pop_int(result);
                if (last_index < 0 || last_index >= context->size)
                {
                    printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                    return true;
                }
                // we need to create a new value with the type of the last value
                int8_t type = context->types[last_index];
                BruterInt index = br_new_var(context, (BruterValue){.i = type}, NULL, BR_TYPE_ANY);
                bruter_push(result, (BruterValue){.i = index}, NULL, 0);
            }
            else if (strcmp(current_word + 1, "index") == 0) // index attribute
            {
                // we need to get the last value from the result
                BruterInt last_index = bruter_pop_int(result);
                if (last_index < 0 || last_index >= context->size)
                {
                    printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                    return true;
                }
                // we need to create a new value with the index of the last value
                BruterInt index = br_new_var(context, (BruterValue){.i = last_index}, NULL, BR_TYPE_ANY);
                bruter_push(result, (BruterValue){.i = index}, NULL, 0);
            }
            else if (strcmp(current_word + 1, ":index") == 0) // index attribute
            {
                // we need to get the last value from the result
                BruterInt last_index = bruter_pop_int(result);
                if (last_index < 0 || last_index >= context->size)
                {
                    printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                    return true;
                }
                // we put the value 
                bruter_push_int(result, context->data[last_index].i, NULL, 0);
            }
            else if (strcmp(current_word + 1, "value") == 0) // value attribute
            {
                // we need to get the last value from the result
                BruterInt last_index = bruter_pop_int(result);
                if (last_index < 0 || last_index >= context->size)
                {
                    printf("BR_WARNING: index %" PRIdPTR " out of range in context of size %" PRIdPTR "\n", last_index, context->size);
                    return true;
                }
                
                // we need to create a new value with the value of the last value
                BruterValue value = context->data[last_index];
                BruterInt index = br_new_var(context, value, NULL, context->types[last_index]);
                bruter_push(result, (BruterValue){.i = index}, NULL, 0);
            }
            else // unknown attribute
            {
                printf("BR_ERROR: unknown attribute %s\n", current_word);
            }
            return true;
        }
    }

    return false;
}

// make sure the next created value is under the specified key, or index
BR_PARSER_STEP(parser_reuse)
{
    BR_PARSER_STEP_BASICS();
    if (current_word[0] == '$') // next key
    {
        BruterList *unused = br_get_unused(context);
		
        // if the next key is a number, we will use it as an index
		if (isdigit(current_word[1]))
        {
            BruterInt index = atol(current_word + 1);
            if (index < 0 || index >= unused->size)
            {
                printf("BR_ERROR: index %" PRIdPTR " out of range in unused list of size %" PRIdPTR "\n", index, unused->size);
                bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
                return false;
            }
			
			// delete the variable at that index, so we can reuse it
            br_clear_var(context, index);
			
            // we put the key to the context
            context->keys[index] = br_str_duplicate(current_word + 1);
        }
		else if (current_word[1] == '$') // force not to reuse a key, but to create a new one
		{
            // we'll need the unused list
            BruterList *unused = br_get_unused(context);

            char* new_name = current_word + 2;
            if (current_word[2] == '\0') // $$ whatever
            {
                // lets push a empty unamed integer
                bruter_push_int(context, 0, NULL, 0);
                bruter_push_int(unused, context->size - 1, NULL, 0);
            }
            else // $$name whatever
            {
                // lets push a empty named integer
                bruter_push_int(context, 0, new_name, 0);
                bruter_push_int(unused, context->size - 1, NULL, 0);
            }
		}
        else
        {
            BruterInt found = bruter_find_key(context, current_word + 1);
            // if the key is not found, we create a new one
            if (found == -1)
            {
                BruterInt index = br_new_var(context, (BruterValue){.p = NULL}, current_word + 1, 0);
                bruter_push(unused, (BruterValue){.i = index}, NULL, 0);
            }
            else 
            {
                // found was a index of the CONTEXT, now we need to find it in the unused list
                found = bruter_find(unused, (BruterValue){.i = found});
    
                if (found != -1) // it is already in the unused list
                {
                    if (unused->size > 1)
                    {
                        // lets just swap it to the end of the unused list
                        bruter_swap(unused, found, unused->size - 1);
                    }
                    else
                    {
                        // nothing to do, the next variable is already the one we want to reuse
                    }
                }
                // it is not in the unused list
                else
                {
                    bruter_push(unused, (BruterValue){.i = found}, NULL, 0);
                }
            }
        }
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_conditional)
{
    BR_PARSER_STEP_BASICS();
    
    if (current_word[0] == '?' && current_word[1] == '\0') // conditional
    {
        // lets verify if we have a next word
        if (splited_command->size <= word_index + 1)
        {
            printf("BR_ERROR: conditional %s has no next word to depend on it\n", current_word);
            // we return true to indicate that we successfully parsed this word, so the parser go to the next word
            return true;
        }
        // lets verify if we have any values on result
        else if (result->size <= 0)
        {
            printf("BR_ERROR: conditional %s has no previous value to check condition\n", current_word);
            // we return true to indicate that we successfully parsed this word, so the parser go to the next word
            return true;
        }
        
        BruterInt last_value = bruter_pop_int(result);
        if (last_value != -1)
        {
            // we found the variable, lets check its type
            if (context->types[last_value] == BR_TYPE_NULL)
            {
                // the only way a existing variable can be false is if its type is null
                // we assume it is false
            }
            else 
            {
                // if the type is not null, we can consider it true
                // ok its true, so lets end this word parsing here
                return true;
            }
        }
        else 
        {
            // we didnt find the variable, so we assume its false
        }

        // if the code reaches here, it means the condition is false
        // lets remove the next word
        void* removed_str = bruter_remove_pointer(splited_command, word_index + 1);

        // and free it
        free(removed_str);

        // we return true to indicate that we successfully parsed the string, so the parser go to the next word
        return true;
    }
    return false;
}

BR_PARSER_STEP(parser_variable)
{
    BR_PARSER_STEP_BASICS();
    BruterInt index = bruter_find_key(context, current_word);
    
    if (index != -1)
    {
        bruter_push(result, (BruterValue){.i = index}, NULL, 0);
        return true;
    }
    else 
    {
        printf("BR_ERROR: variable %s not found\n", current_word);
        bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
        return false;
    }
}

BR_PARSER_STEP(parser_comment)
{
    BR_PARSER_STEP_BASICS();

    // this is a comment parser, it will ignore the next word, doesnt matter what it is
    if (current_word[0] == '/' && current_word[1] == '/')
    {
        // lets verify if we have a next word
        if (word_index + 1 < splited_command->size)
        {
            // lets remove the next word
            void* removed_str = bruter_remove_pointer(splited_command, word_index + 1);

            // and free it
            free(removed_str);
        }

        // we can just return true, because we are not interested in the result
        return true;
    }
    // if it is not a comment, we return false to continue parsing
    return false;
}

BR_PARSER_STEP(parser_spread)
{
    BR_PARSER_STEP_BASICS();

    // this is a spread parser, it will expand the list into the result
    if (current_word[0] == '.' && current_word[1] == '.' && current_word[2] == '.')
    {
        BruterInt found = bruter_find_key(context, current_word + 3);
        BruterList *spread_list = NULL;
        if (found == -1)
        {
            printf("BR_ERROR: spread variable %s not found\n", current_word + 3);
            bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
            return false;
        }
        else if (context->types[found] != BR_TYPE_LIST)
        {
            printf("BR_ERROR: spread variable %s is not a list\n", current_word + 3);
            bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
            return false;
        }

        // we will expand the list into the result
        spread_list = (BruterList*)context->data[found].p;
        for (BruterInt i = 0; i < spread_list->size; i++)
        {
            // we push each element of the list into the result
            bruter_push(result, spread_list->data[i], NULL, 0);
        }

        // we return true to indicate that we successfully parsed the string, so the parser go to the next word
        return true;
    }
    // if it is not a spread, we return false to continue parsing
    return false;
}

// note: this is not direcly part of default parser, 
// is not meant to be used by the user direcly,
// but if you want to, just add it to the parser before baking a function
// it will be used to parse function arguments, like %0, %1, etc.
// remove it from the parser after baking a function, so remove its overhead and avoid conflict with other parser steps
BR_PARSER_STEP(parser_function_arg)
{
    BR_PARSER_STEP_BASICS();

    // this is a function argument parser, it will be added to the parser just when baking a function
    if (current_word[0] == '%' && isdigit(current_word[1]))
    {
        BruterInt index = atol(current_word + 1);

        // we use negative index to indicate that this is a function argument
        // while -1 is usually used for errors, we can use it here because baked function SHOULD NOT have any errors
        // so we can safely use -1 as a special value for function arguments
        bruter_push_int(result, -index - 1, NULL, 0);
        return true;
    }
    else if (current_word[0] == '.' && current_word[1] == '.' && current_word[2] == '.' && current_word[3] == '%') // spread arguments
    {
        // this is a special if the use wanna spread the arguments in this exact place
        // we will push a special value to indicate that this is a spread argument
        // we use BR_SPECIAL_RETURN to indicate a spread argument
        bruter_push_int(result, BR_SPECIAL_RETURN, NULL, 0);
        // we return true to indicate that we successfully parsed the string, so the parser go to the next word
        return true;
    }

    // if it is not a function argument, we return false to continue parsing
    return false;
}

BR_PARSER_STEP(parser_function)
{
    BR_PARSER_STEP_BASICS();
    

    
    if (current_word[0] == '(' && current_word[1] == '%')
    {
        const char* temp = NULL;
        bool need_args = false; // we will check if the function needs arguments
        BruterInt baked = -1;
        BruterList *list_ptr = NULL;
        
        bruter_unshift(parser, (BruterValue){.step = parser_function_arg}, "std_function", 0);
        current_word[strlen(current_word) - 1] = '\0'; // remove the closing parenthesis

        temp = current_word + 2;
        while (current_word[0] == ' ' || current_word[0] == '\t' || current_word[0] == '\n' || current_word[0] == '\r') // remove leading spaces
        {
            temp++;
        }

        baked = br_bake_code(context, parser, temp); // bake the function

        list_ptr = (BruterList*)bruter_get_pointer(context, baked);
        
        if (unlikely(list_ptr == NULL))
        {
            printf("BR_ERROR: failed to get baked function from context\n");
            bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
            return false;
        }

        for (BruterInt i = 0; i < list_ptr->size; i++)
        {
            const BruterList *current_list = (BruterList*)context->data[list_ptr->data[i].i].p;
            for (BruterInt j = 0; j < current_list->size; j++)
            {
                if (current_list->data[j].i < 0) // if the argument is a function argument
                {
                    need_args = true;
                    break;
                }
            }
            if (need_args) break; // no need to check further, we already know that
        }

        // baked is faster than function, but doesnt have arguments, thats why
        if (need_args)
        {
            context->types[baked] = BR_TYPE_USER_FUNCTION; // set the type to function
        }
        else
        {
            context->types[baked] = BR_TYPE_BAKED; // set the type to baked
        }

        bruter_shift_int(parser); // remove the std_function from the parser

        if (baked == -1)
        {
            printf("BR_ERROR: failed to bake function from %s\n", temp);
            bruter_push(result, (BruterValue){.i = -1}, NULL, 0);
            return false;
        }
        else
        {
            bruter_push(result, (BruterValue){.i = baked}, NULL, 0);
            return true;
        }
    }
    return false;
}

// evatuation steps
// evatuation steps
// evatuation steps
// evatuation steps
// evatuation steps
// evatuation steps
// evatuation steps

BR_EVALUATOR_STEP(eval_step_function)
{
    if (br_arg_get_type(context, args, -1) == BR_TYPE_FUNCTION)
    {
        BruterInt result = bruter_call(context, args);
        if (result >= 0)
        {
            // if the result is valid, we return it
            return result;
        }

        // special return to interrupt the evaluation, because we already found a step that can handle this type
        return BR_SPECIAL_RETURN; 
    }
    
    // it is not the type we are looking for;
    return -1;
};

BR_EVALUATOR_STEP(eval_step_buffer)
{
    if (br_arg_get_type(context, args, -1) == BR_TYPE_BUFFER)
    {
        // we will evaluate the buffer as a command
        BruterInt result = br_eval(context, (char*)br_arg_get_pointer(context, args, -1));
        if (result >= 0)
        {
            // if the result is valid, we return it
            return result;
        }

        // special return to interrupt the evaluation, because we already found a step that can handle this type
        return BR_SPECIAL_RETURN;
    }

    // it is not the type we are looking for;
    return -1;
};

BR_EVALUATOR_STEP(eval_step_list)
{
    if (br_arg_get_type(context, args, -1) == BR_TYPE_LIST)
    {
        // we will evaluate the list as a command
        BruterInt result = bruter_call(context, args);
        if (result >= 0)
        {
            // if the result is valid, we return it
            return result;
        }

        // special return to interrupt the evaluation, because we already found a step that can handle this type
        return BR_SPECIAL_RETURN;
    }

    // it is not the type we are looking for;
    return -1;
};

BR_EVALUATOR_STEP(eval_step_baked)
{
    if (br_arg_get_type(context, args, -1) == BR_TYPE_BAKED)
    {
        // we will evaluate the baked code as a command
        BruterList *compiled = (BruterList*)br_arg_get_pointer(context, args, -1);
        BruterInt result = br_baked_call(context, compiled);
        if (result >= 0)
        {
            // if the result is valid, we return it
            return result;
        }

        // special return to interrupt the evaluation, because we already found a step that can handle this type
        return BR_SPECIAL_RETURN;
    }

    // it is not the type we are looking for;
    return -1;
};

BR_EVALUATOR_STEP(eval_step_user_function)
{
    // a user-defined function
    if (br_arg_get_type(context, args, -1) == BR_TYPE_USER_FUNCTION)
    {
        BruterList *compiled = (BruterList*)br_arg_get_pointer(context, args, -1);
        BruterList *temp_list = bruter_new(sizeof(void*), false, false);
        
        // special return to interrupt the evaluation
        BruterInt result = BR_SPECIAL_RETURN;
        
        for (BruterInt i = 0; i < compiled->size; i++)
        {
            BruterList *current_command = (BruterList*)bruter_get_pointer(context, compiled->data[i].i);
            if(unlikely(current_command == NULL))
            {
                printf("BR_ERROR: command %" PRIdPTR " is NULL in user function\n", i);
                bruter_free(temp_list);

                // special return to interrupt the evaluation
                return BR_SPECIAL_RETURN;
            }

            // we will create a temporary list to store the arguments for the command
            for (BruterInt j = 0; j < current_command->size; j++)
            {
                // unlikely because we expect most of the arguments not to be provided by the user
                if (unlikely(current_command->data[j].i < 0)) // if a function argument
                {
                    if (current_command->data[j].i == BR_SPECIAL_RETURN) // if it is a spread argument
                    {
                        // we will spread the arguments from the args list
                        // UInt is used to avoid signed integer overflow
                        for (BruterUInt k = 0; k < (BruterUInt)br_arg_get_count(args); k++)
                        {
                            bruter_push_int(temp_list, br_arg_get_index(args, (BruterInt)k), NULL, BR_TYPE_ANY);
                        }
                    }
                    else
                    {
                        // if index is %0, we will use args->data[1]
                        // convert to positive index
                        BruterInt arg_index = -current_command->data[j].i - 1;
                        if (unlikely(arg_index < 0 || arg_index >= args->size))
                        {
                            printf("BR_ERROR: argument index %" PRIdPTR " out of range in args of size %" PRIdPTR "\n", arg_index, args->size);
                            
                            // special return to interrupt the evaluation
                            return BR_SPECIAL_RETURN;
                        }
                        bruter_push_int(temp_list, br_arg_get_index(args, arg_index), NULL, BR_TYPE_ANY);
                    }
                }
                else
                {
                    // we can just push the value as it is
                    bruter_push(temp_list, current_command->data[j], NULL, 0);
                }
            }
            result = bruter_call(context, temp_list);
            if (result > -1)
            {
                // if the result > -1, we can break the loop
                break;
            }

            // clear the temp_list for the next command
            temp_list->size = 0;
        }
        bruter_free(temp_list);

        // if the result is valid, we return it
        if (result >= 0)
        {
            return result;
        }
        
        // special return to interrupt the evaluation, because we already found a step that can handle this type
        return BR_SPECIAL_RETURN;
    }
    // means is not the type we are looking for
    return -1;
};

// default parser
// the order of the steps is important, because the parser will try to match the first step that returns true
// some are positioned just for performance reasons, but most of them are positioned in a way that they will not conflict with each other
BruterList* br_default_parser(BruterList* context)
{
    BruterList *_parser = br_get_parser(context);
    
    bruter_push(_parser, (BruterValue){.step = parser_function}, "function", 0);
    bruter_push(_parser, (BruterValue){.step = parser_expression}, "expression", 0);
    bruter_push(_parser, (BruterValue){.step = parser_string}, "string", 0);
    bruter_push(_parser, (BruterValue){.step = parser_number}, "number", 0);
    bruter_push(_parser, (BruterValue){.step = parser_attr_get}, "attr_get", 0);
    bruter_push(_parser, (BruterValue){.step = parser_attr}, "attr", 0);
    bruter_push(_parser, (BruterValue){.step = parser_reuse}, "reuse", 0);
    bruter_push(_parser, (BruterValue){.step = parser_list}, "list", 0);
    bruter_push(_parser, (BruterValue){.step = parser_char}, "char", 0);
    bruter_push(_parser, (BruterValue){.step = parser_spread}, "spread", 0);
    bruter_push(_parser, (BruterValue){.step = parser_comment}, "comment", 0);
    bruter_push(_parser, (BruterValue){.step = parser_conditional}, "conditional", 0);
    bruter_push(_parser, (BruterValue){.step = parser_variable}, "variable", 0);
    
    return _parser;
}

BruterList* br_default_evaluator(BruterList* context)
{
    BruterList *_evaluator = br_get_evaluator(context);

    bruter_push(_evaluator, (BruterValue){.eval_step = eval_step_function}, "function", 0);
    bruter_push(_evaluator, (BruterValue){.eval_step = eval_step_buffer}, "buffer", 0);
    bruter_push(_evaluator, (BruterValue){.eval_step = eval_step_list}, "list", 0);
    bruter_push(_evaluator, (BruterValue){.eval_step = eval_step_baked}, "baked", 0);
    bruter_push(_evaluator, (BruterValue){.eval_step = eval_step_user_function}, "user_function", 0);
    
    return _evaluator;
}

BR_INIT(bruterlang)
{
    // we will set the default parser and evaluator for the context
    br_default_parser(context);
    br_default_evaluator(context);
}
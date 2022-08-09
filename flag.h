typedef struct foption_s {
    char            *name; // the name of the argument
    /**
     * @brief the function used to parse the argument
     * it should return a zero to indicate success
     * @param arg the argument being parsed
     * @param value the value of the argument being parse 
     * (for boolean argument it's not possible to write something like --arg true so in 
     * this case the handler will not get true as the value but NULL and it will treat it as NULL)
     * 
     */
    int             (*handler) (char *arg, char *value, void *var); 
    void            *var;
    char            *description;
    unsigned int    flags;
    char            shorthand;
} flag_option_t;

// TODO: need to implement default value


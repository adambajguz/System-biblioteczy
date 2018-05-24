/*
 * A code snippet used in:
 * Books()
 * Users()
 * UserDetails()
 *
 * to print current list view mode sort dirrection
 */

    printf("' ");

    switch(sortedway)
    {
    case UPPER:
        printf("od zdanych ksi\xA5\xBE\x65k ");
        break;

    case LOWER:
        printf("od wypo\xBEyczonych ksi\xA5\xBE\x65k");
        break;
    };

    printf(".\n");
    setDcolor();
}
//END

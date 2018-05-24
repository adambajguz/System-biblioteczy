/*
 * A code snippet used in:
 * Books()
 * Users()
 *
 * to provide ESC key action.
 */

else if(key==27) // <ESC> action
{
    if(arg==1||arg==2) // only when access to Books function from BookBorrow function
        ret.menucmd=NO_JUMP;
    break;
}

#include "evaluator.h"
#include "ast.h"
#include "assignment.h"
#include "misc.h"

#define Iff(a, b) (a&&b)||((!a)&&(!b)) /* Macros para el operador "si solo si" */
#define Implica(a, b) ((!a)||b) /* Macros para el operador "implica" */

int eval(ASTNode *f, Asgmnt *a)
{

  Asgmnt *a2;
  int resultado = 0;
  int o1, o2, an1, an2, n, if1, if2, im1, im2;

  switch (f->type)
  {
    case PROP:
      ASSIGNMENT_FIND(a,&f->id,a2);
      if (a2 == NULL) {return -1;}
      else {return a2->value;}

    case OR:
      o1 = eval(f->l_succ,a);
      o2 = eval(f->r_succ,a);

      if (o1 == -1 || o2 == -1) {resultado = -1;}
      else {resultado = o1 || o2;}

      return resultado;

    case AND:
      an1 = eval(f->l_succ,a);
      an2 = eval(f->r_succ,a);

      if (an1 == -1 || an2 == -1) {resultado = -1;}
      else {resultado = an1 && an2;}

      return resultado;

    case NOT:
      n = eval(f->l_succ,a);

      if (n == -1) {resultado = -1;}
      else {resultado = !n;}

      return resultado;

    case IFF:
      if1 = eval(f->l_succ,a);
      if2 = eval(f->r_succ,a);

      if (if1 == -1 || if2 == -1) {resultado = -1;}
      else {resultado = Iff(if1, if2);}

      return resultado;

    case IMPL:
      im1 = eval(f->l_succ,a);
      im2 = eval(f->r_succ,a);

      if (im1 == -1 || im2 == -1) {resultado = -1;}
      else {resultado = Implica(im1, im2);}

      return resultado;
  }

  return 0;
}

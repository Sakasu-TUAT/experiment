#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "name.h"

struct name_info_ {
  char *str;
  name_stat stat;
  name_type type;
  int idnum;
};

struct name_list_ {
  name_info info;
  name_list *next;
};

name_info *
name_find(name_list *p, char const s[])
{
  name_list *index;

  index = p;

  while (index != 0)
    {
      if (strcmp(s, index->info.str) == 0)
        break;

      index = index->next;
    }

  return (index == 0) ? 0 : (&(index->info));
}

name_list *
name_append(name_list *p, char *s)
{
  name_list *newname;

  newname = malloc(sizeof(name_list));
  newname->info.str = s;
  newname->info.stat = NAME_UNKNOWN;
  newname->info.idnum = 0;
  newname->next = p;

  return newname;
}

void
name_list_free(name_list *p)
{
  name_list *next;

  while (p != 0)
    {
      next = p->next;;
      free(p->info.str);
      free(p);
      p = next;
    }
}

void
name_set_decl(name_info *p)
{
  p->stat = NAME_DECLARED;
}

void
name_set_def(name_info *p)
{
  p->stat = NAME_DEFINED;
}

void
name_set_proc(name_info *p)
{
  p->type = NAME_PROC;
}

void
name_set_glo_var(name_info *p)
{
  p->type = NAME_GLO_VAR;
}

void
name_set_loc_var(name_info *p)
{
  p->type = NAME_LOC_VAR;
}

name_stat
name_get_stat(name_info const *p)
{
  return p->stat;
}

name_type
name_get_type(name_info const *p)
{
  return p->type;
}

void
name_set_id(name_info *p, int id)
{
  p->idnum = id;
}

int
name_get_id(name_info const *p)
{
  return p->idnum;
}

char const *
name_get_str(name_info const *p)
{
  return p->str;
}

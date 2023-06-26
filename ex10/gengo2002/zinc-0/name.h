#if !defined _NAME_H_
#define _NAME_H_

typedef enum name_stat {
  NAME_UNKNOWN,
  NAME_DECLARED,
  NAME_DEFINED
} name_stat;

typedef enum name_type {
  NAME_PROC,
  NAME_GLO_VAR,
  NAME_LOC_VAR
} name_type;

typedef struct name_info_ name_info;
typedef struct name_list_ name_list;

name_info *name_find(name_list *p, char const s[]);
name_list *name_append(name_list *p, char *s);
void name_list_free(name_list *p);
void name_set_decl(name_info *p);
void name_set_def(name_info *p);
void name_set_proc(name_info *p);
void name_set_glo_var(name_info *p);
void name_set_loc_var(name_info *p);
name_stat name_get_stat(name_info const *p);
name_type name_get_type(name_info const *p);
char const *name_get_str(name_info const *p);
void name_set_id(name_info *p, int id);
int name_get_id(name_info const *p);

#endif /* _NAME_H_ */

#ifndef _STDARG_H
#define _STDARG_H

typedef char* va_list;

#define _internal_va_size(v) (((sizeof(v) + sizeof(int) - 1) / (sizeof(int))) * (sizeof(int)))

#define va_start(ap, var) ((ap) = ((va_list)&var - _internal_va_size(var)))

#define va_arg(ap, type) (((ap) = (ap - _internal_va_size(type))), (*((type*) (ap + _internal_va_size(type)))))

#define va_end(ap) ((void)0)


#endif // _STDARG_H
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <string.h>
#include <stdio.h>
#include "matrix.h"
#include "error_types.h"


int main(void)
{
    int status = SUCCESS;
    
    char *mode = NULL;
    size_t len = 0;

    if (getline(&mode, &len, stdin) == -1)
        status = INP_ERR;
    else if (strcmp(mode, "out\n") == 0)
    {
        matrix_t mat = m_init();
        status = m_input(&mat);
        if (status == SUCCESS)
            m_print(&mat);
        m_destroy(&mat);
    }
    else if (status == SUCCESS && strcmp(mode, "add\n") == 0)
    {
        matrix_t m1 = m_init(), m2 = m_init(), res = m_init();

        status = m_input(&m1);
        if (status == SUCCESS)
            status = m_input(&m2);

        if (status == SUCCESS)
            status = m_sum(&res, &m1, &m2);

        if (status == SUCCESS)
            m_print(&res);

        m_destroy(&m1);
        m_destroy(&m2);
        m_destroy(&res);
    }
    else if (status == SUCCESS && strcmp(mode, "mul\n") == 0)
    {
        matrix_t m1 = m_init(), m2 = m_init(), res = m_init();

        status = m_input(&m1);
        if (status == SUCCESS)
            status = m_input(&m2);

        if (status == SUCCESS)
            status = m_mul(&res, &m1, &m2);
        
        if (status == SUCCESS)
            m_print(&res);

        m_destroy(&m1);
        m_destroy(&m2);
        m_destroy(&res);
    }
    else if (status == SUCCESS && strcmp(mode, "lin\n") == 0)
    {
        matrix_t mat = m_init();

        status = m_input(&mat);

        if (status == SUCCESS)
            status = m_maxrow_del(&mat);

        if (status == SUCCESS)
            m_print(&mat);
        
        m_destroy(&mat);
    }
    else
        status = OP_ERR;

    return status;
}
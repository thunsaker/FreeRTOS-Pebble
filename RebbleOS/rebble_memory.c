/* 
 * This file is part of the RebbleOS distribution.
 *   (https://github.com/pebble-dev)
 * Copyright (c) 2017 Barry Carter <barry.carter@gmail.com>.
 * 
 * RebbleOS is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * RebbleOS is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "stdio.h"
#include "string.h"
#include "rebble_memory.h"

// heap4 doesn't have calloc
void *pvPortCalloc(size_t count, size_t size)
{
    void *x = pvPortMalloc(count * size);
    if (x != NULL)
        memset(x, 0, count * size);
    return x;
}

/*
 * Alloc and set memory. Basic checks are done so we don't 
 * hit an exception or ask for stoopid sizes
 */
void *rbl_calloc(size_t count, size_t size)
{
    if (size > xPortGetFreeHeapSize())
    {
        printf("Malloc fail. Not enough heap for %d\n", size);
        return NULL;
    }
    
    if (size > 100000)
    {
        printf("Malloc will fail. > 100Kb requested\n");
        return NULL;
    }
    
    return pvPortCalloc(1, size);
}

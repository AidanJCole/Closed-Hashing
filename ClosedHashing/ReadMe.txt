========================================================================
    CONSOLE APPLICATION : ClosedHashing Project Overview
========================================================================

A simple implementation of a hash table. Notable is that it has better insertion performance that the teachers provided equation for performance.

The given equation for optimal performance was 1/(1-a), with a as the load factor, or entries/total size.

As this implementation beats the "optimal," I knew something was up, and derived the real optimal equation: ((n+1)(n-x))/((x-n-1)(x-n)), where x is the number of entries and n is the size of the hash table.
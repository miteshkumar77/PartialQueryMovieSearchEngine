HOMEWORK 9: IMDB SEARCH

NAME:  <Mitesh Kumar>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <25>


HASH FUNCTION DESCRIPTION

I used the hash function provided in lab 10. It differs
based on the order of the characters which is necessary since Order of the Genres, Roles
and Actors matter in our query.

HASH TABLE IMPLEMENTATION

I wrote a combination algorithm to replace each of the 6 
parameters with a place holder character instead of the
actual contents, for all combinations. When any partial
query is made, we can jump to the list that contains all 
of the hashes that match the query's hash.  

The partial queries are stored in a vector of pairs with the key
as the first value and a list of all of the items with that key
if that key is ever hashed. (All possible keys are not generated)
A collision is defined as 2 items with differing keys having the
same key % m_table.size() value. We linear probe if ever the list
of movie pointers at m_table[key % m_table.size()] is not empty and
doesn't match the key of the partial query we want to insert. 
We keep going forward until we find an empty list or a list with
matching key. m_size is the number of unique keys contained by the
list. The number of pointers stored by the hash table may be much
larger. This is okay since each list is a unit and only its entirity 
can be retrieved. There is no need to retrieve individual values from
each list. Only all. Resize remaps each non-empty list to a position
in a new vector of double the original size. The individual pointers 
stay together. Query hashes the inputted query in the same format
that the partial queries from each movie are hashed for storage. 
Query then jumps to its hash % m_table.size() in m_table and 
linearly probes until either an empty list is found or a list
with matching key is found. Then this list is returned. If
it is empty then we format our output accordingly. The size
is known immediately upon retrieval of the list, since std::list
keeps track of number of elements. Note* Infinite while loops are
impossible since we never allow the hash table to be completely full
unless specified by the user which is a user error. 

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



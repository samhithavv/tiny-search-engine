# CS50 TSE - Querier Design
## Samhitha Vallury - github: samhithavv

Querier:

Inputs and Outputs:
Inputs: User-provided queries from stdin. Program reads thequeries, tokenizes them, checks if its correct, and then uses it to search.
Outputs: Displays the documents that have the word ranked by how many times the word appears. Checks for errors and then displays error messages.

Functional Decomposition into Modules:
printCleanQuery: Prints the query with proper white space
processQuery: Intersects/unionizes counters based on the query
checkQueries: Handles user input, checks it, and searches it depending on the queries
tokenizeQuery: Tokenizes the query based on spaces.
validateQuerySyntax: Checks the tokenized query.

Major Functions:
checkQueries
Loops through to read user input, checks it, makes it into a token, and passes it to be processed more.

processQuery
Processes the query, intersects and combines the counters, then returns the result.

tokenizeQuery
"Tokenizes" the query into distinct words, which removes any bad whitespace and ignores invalid input.

Major Data Structures:
counters_t: Stores the document ID and score pairs for counting word occurrences.
index_t:  Mapping from words to counters_t objects and essentially represents the word occurrences across documents.
char** tokens: Array for each word in the query

Ranking
Inputs and Outputs:
Inputs: Receives counters with document scores and a list of documents
Outputs: prints documents ordered by rank, from highest to lowest score.

Functional Decomposition into Modules:
printRankedResults: Displays ranked documents based on scores.
findMaxScoreDoc: Finds the document with the highest score in the counters.
countDocsHelper: Helper function to count documents with non-zero scores.

Major Functions:
printRankedResults
Prints all matched documents in descending order by score. Loads the webpages to get the applicable URLs

findMaxScoreDoc
Scans counters to find the document with the highest scoree

Major Data Structures:
counters_t: Holds document scores .
webpage_t: Stores webpage data like URL and ID 

Iterators

Inputs and Outputs:
Inputs: takes in counters and index structures to copy and iterate 
Outputs: Returns modified or combined counters based on the prompt

Functional Decomposition into Modules:
counters_duplicate: Makes a copy of a counters object
counters_intersect: Makes an intersection of counters objects.
counters_union: Unionizes counters

Major Functions
counters_duplicate
Creates a duplicate of a counters object 

counters_intersect
Returns a new counters object containing the minimum counts of items found in both input counters.

counters_union
Returns a new counters object with combined counts from both counters

Major Data Structures
counters_t: Used as the structure for storing and iterating over document scores and counts
# CS50 TSE - Querier Implementation
## Samhitha Vallury - github: samhithavv


Querier
The querier module is accepts user input, processes queries, and displays ranked results based on their relevance.

Initialization and Setup:

The querier program starts by loading the index and page directory. The index contains mappings from words to documents that contain those words, along with how many times they appear. The page directory is used to retrieve the URLs for each document.

User Query Processing:

The querier prompts the user to enter a search query, which is then normalized by converting to lowercase.
The program  checks the syntax of the query. This ensures that logical operators (like AND or OR) are used correctly, which includes not appearing at the beginning or end of the query, and they shouldn’t appear in sequence without a search term in between.
If the syntax is valid, the query is split into tokens (words and operators), and the processQuery function is called to search for documents matching the query terms.

Query Execution:

processQuery processes the tokens in the query one by one. It looks at logical operations (AND, OR) to refine search results:
AND means that both terms surrounding it must be present in the document. So if a query says cats AND dogs, only documents containing both cats and dogs will be considered.
OR means either term can be matched. The querier retrieves documents that contain each search term and combines result depending on what the user input is.

Displaying Results:

If matching documents are found, they are passed to the ranking module to be scored and ranked based on relevance. The documents are then displayed in order of their relevance score.
If no matches are found, the program displays "No matches found."

Iterators
The iterators module traverses the data structures used by the querier and ranking modules. There are three primary iterators, which are for intersection, unionizing, and duplicating, which get passed into counters_iterate and hashtable iterate. 

Intersection Iterator:

The intersection iterator gets two common elements between two sets 
For each document in the first set, it checks if the document also exists in the second set.
If it does, it takes the minimum frequency between the two sets for that document. This ensures that only documents containing both terms are kept, and their score is limited by the term that appears least frequently.

Union Iterator:

The union iterator combines elements from two sets, useful for queries using an OR operator.
It adds all elements from both sets to the result set, taking the maximum frequency when a document exists in both sets.
Any document with either owrd in it gets included in the results, and then the documents with both get a higher score than the others

Duplicate Iterator:

The duplicate iterator duplicates an existing set, often as a starting point for processing.
It creates a copy of all elements in the original set into a new set or counter.
This is used to initialize a result set without changing the origin , making sure that any changes do not affect the original version.

Ranking
The ranking module assigns a score to each document based on  how many words it has in within in relation to the query. 


Processing the Query Terms:

processQuery processes the tokens and uses the query’s  structure based on or or and to combine the results from  multiple documents.
For each word in the query, ranking looks up the word in the index, getting a list of documents containing that word along with their counts (frequencies).
AND logic requires taking the minimum frequency among the terms (since both terms must be there), while OR logic requires a union of results.

Scoring Documents:

Once a combined list of matching documents is created, each document is given a score based on the term frequencies. For example, a document that contains the query terms frequently will score higher than one where the terms are not as frequent.
This score is stored in a counters structure, with each document ID as a key and its score as the value.

Finding and Displaying Ranked Results:

The printRankedResults function takes the scored documents and sorts them by score, printing them to the console  from highest to lowest relevance.

It accomplishes this by repeatedly finding the document with the maximum score using findMaxScoreDoc, printing it, and resetting that document’s score to zero in the counters. This process is repeated until all documents with scores have been printed.
Each document’s URL and score are displayed alongside the result, displaying a list of the most relevant matches.

Crawler: Cntains code for crawler, which goes through a webpage and collects the URLs within it. It will then examine those new URLs depending on the depth.

Indexer: Contains code for crawler, which goes through output of crawler and then collects words greater than or equal to length and counts how many time it appears in each document. 

Querier: The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

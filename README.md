# nosqldb--cpp

A Key-Value database built in C++.
Idea based on the project description of the Object Oriented Design course by [Prof. Jim Fawcett](https://ecs.syr.edu/faculty/fawcett/handouts/webpages/fawcettHome.htm "Prof. Jim Fawcett")

### Features
- Add key-value based entries to the database
    - Values contain 2 parts - Metadata and Payload
    - Payload can be any Object which implements the IPayload interface
	- Metadata will allow to set description and add child relationships

- A Query interface which supports query on
    - keys: eq & regex
	- datetime: between, gt, lt
	- metadata description: regex
	- child key: eq
	- payload: custom criteria
	- AND & OR queries on combination of above
	
- A Persistence interface which supports 
    - serializing the DB or a query subset to XML
	- importing data from XML to DB

# CS-109-Advanced-Programming



# TITLE

* Date: Monday, February 7, 2022
* Status: On Progres 
* Deciders: Allan, Christian, Maciej, Marian 

Technical Story: 

CI-CD pipelines on the ADI project.

## Context and Problem Statement
We would lile to improve the CI-CD pipelines on ADI project focusing on : 
1.  Creting the infrastructure on GCP (CI)
2.  Deploying the code on the created infrastructure (CD)
3.  Brush up the testing process


## Decision Drivers <!-- optional -->

The ADI api is deployed on one production GCP project. 
a. The CI is acomplished using python scripts which calls gcloud commands. 
b. The CD is acomplished using GitHub actions
c  Testing is performed only for one cloud run service.

## Considered Options

In order to improve the testing coverage, we are considering creating another ADI-staging project. 
We would like to avoid affecting the production env while we are running our tests. 

Therefore we should decide about the tools we are going to use for creating the CI-CD pipeline: 
a. CI : Terraform or GCP Deployment Manager 
b. CD : GitHub Actions or Cloud Build 


## CI: Pros and Cons of the Options <!-- optional -->

### Terraform 

[example | description | pointer to more information | …] <!-- optional -->

* Good, because [argument a]
* Good, because [argument b]
* Bad, because [argument c]
* … <!-- numbers of pros and cons can vary -->

### Deployment Manager 

[example | description | pointer to more information | …] <!-- optional -->

* Good, because [argument a]
* Good, because [argument b]
* Bad, because [argument c]
* … <!-- numbers of pros and cons can vary -->

## CD: Pros and Cons of the Options <!-- optional -->

### Github Actions

[example | description | pointer to more information | …] <!-- optional -->

* Good, because [argument a]
* Good, because [argument b]
* Bad, because [argument c]
* … <!-- numbers of pros and cons can vary -->

### Cloud Build  

[example | description | pointer to more information | …] <!-- optional -->

* Good, because [argument a]
* Good, because [argument b]
* Bad, because [argument c]
* … <!-- numbers of pros and cons can vary -->


## Decision Outcome


## Links <!-- optional -->

* [Link type] [Link to ADR] <!-- example: Refined by [ADR-0005](0005-example.md) -->
* … <!-- numbers of links can vary -->


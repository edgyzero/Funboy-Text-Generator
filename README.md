# Funboy-Text-Generator
Generates semi-random text from categorical user defined lists.
# Description
Allows a user to create a category of seperated text. A category can be named anything and is indicated by < >. Once the user has added a category they can use the generate command to resolve the category to a random entry within. This program allows for nesting of these categories so that one could create a category \<sentence\> containing the following categories: \<article\> \<noun\> \<past-tense-verb\> \<article\> \<noun\>. When generating a category containing other cateogires the program will recursivey traverse the categories until finding one with no more categories. Once it has done this it will then select a randomy entry form that category. The end result for generate \<sentence\> could be something like: "A cat licked the couch."
# Usage
The following is an example of what a typical use case for this program would be:
![Screenshot](Example.png)

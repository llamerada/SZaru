= Ruby Binding of SZaru

== Introduction
SZaru is a library to use {Sawzall}[http://code.google.com/p/szl/] aggregators in pure C++, Ruby and Python.
Currently, I have implemented the following 3 aggregators:
[Top] Statistical samplings that record the 'top N' data items based on CountSketch algorithm from "Finding Frequent Items in Data Streams", Moses Charikar, Kevin Chen and Martin Farach-Colton, 2002.
[Unique] Statistical estimators for the total number of unique data items.
[Quantile] Approximate N-tiles for data items from an ordered domain based on the following paper: Munro & Paterson, "Selection and Sorting with Limited Storage", Theoretical Computer Science, Vol 12, p 315-323, 1980.

== Example
 require "szaru"
 unq_est = SZaru::UniqueEstimator.new(10)
 1000.times do |i|
   unq_est.add_elem(i.to_s + "test")
 end
 puts unq_est.estimate # => 913

== License

 Copyright 2010 Yuji Kaneda
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
      http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
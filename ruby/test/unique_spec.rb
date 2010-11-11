require File.join(File.dirname(__FILE__), "../ext/szaru")

include SZaru
describe UniqueEstimator do
  it "return 0 if no addition exists" do
    ue = UniqueEstimator.new(10)
    ue.estimate.should == 0
  end

  it "return 0 if max_elems is 0" do
    ue = UniqueEstimator.new(0)
    ue.add_elem("test")
    ue.estimate.should == 0
  end

  it "return exact number when the number of elements is small than max_elems" do
    ue = UniqueEstimator.new(10)
    5.times do |i|
      ue.add_elem("test#{i}")
    end
    ue.estimate.should == 5
  end

  it "return approximate number when the number of elements is greater than max_elems" do
    ue = UniqueEstimator.new(10)
    n_unique = 997
    elems = Array.new(n_unique){|i| ("test#{i}") }
    # add elems to ue 2 times in random oreder
    2.times do 
      elems.sort_by{ rand }.each do |elm|
        ue.add_elem(elm)
      end
    end
    diff = ue.estimate - n_unique
    error_rate = ( diff / n_unique.to_f).abs
    error_rate.should < 0.1
  end
  
end

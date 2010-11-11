require File.join(File.dirname(__FILE__), "../ext/szaru")

include SZaru
top_estimators = [TopEstimator::Int32, TopEstimator::Int64, TopEstimator::Double]

def convert_value_from_index(index, value)
  case index
  when 0, 1
    value.to_i
  when 2
    value.to_f
  end
end

top_estimators.each_with_index do |top_estimator, te_index|
  describe top_estimator do
    it "return [] if no addition exists" do
      te = top_estimator.new(10)
      te.estimate.should == []
    end

    it "return [] if top_elems is 0" do
      te = top_estimator.new(0)
      te.add_elem("test")
      te.estimate.should == []
    end

    it "return exact number when the number of elements is small than top_elems" do
      te = top_estimator.new(10)
      n_elemnts = 5
      n_elemnts.times do |i|
        te.add_elem("test#{i}")
        te.add_weighted_elem("test#{i}", convert_value_from_index(te_index, i))
      end
      top_elements = te.estimate
      top_elements.length.should == n_elemnts
      n_elemnts.times do |i|
        # check element
        top_elements[i][0].should == "test#{n_elemnts - i - 1}"
        # check weight
        exact_weight = convert_value_from_index(te_index, n_elemnts - i)
        top_elements[i][1].should == exact_weight
      end
    end

  end
end

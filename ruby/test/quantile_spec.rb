require File.join(File.dirname(__FILE__), "../ext/szaru")

include SZaru
quantile_estimators = [QuantileEstimator::Int32, QuantileEstimator::Int64, QuantileEstimator::Double]

def convert_value_from_index(index, value)
  case index
  when 0, 1
    value.to_i
  when 2
    value.to_f
  end
end

quantile_estimators.each_with_index do |quantile_estimator, te_index|
  describe quantile_estimator do
    it "return [0] if no addition exists" do
      te = quantile_estimator.new(10)
      te.estimate.should == [0]
    end

    it "return [min, max] if quantile_elems is 0" do
      te = quantile_estimator.new(0)
      te.add_elem(convert_value_from_index(te_index, 10))
      te.add_elem(convert_value_from_index(te_index, 7))
      te.estimate.should == [7, 10]
    end

    it "return exact quantile when the number of elements is small than quantile_elems" do
      te = quantile_estimator.new(10)
      n_elemnts = 5
      n_elemnts.times do |i|
        te.add_elem(convert_value_from_index(te_index, i))
      end
      quantile_elements = te.estimate
      expexcted_values = [0, 0, 1, 1, 2, 2, 3, 3, 4, 4]
      expexcted = expexcted_values.map{|value| convert_value_from_index(te_index, value)}
      quantile_elements.should == expexcted
    end

    it "return same result when calling estimate twice" do
      te = quantile_estimator.new(10)
      n_elemnts = 5
      n_elemnts.times do |i|
        te.add_elem(convert_value_from_index(te_index, i))
      end
      # first call
      quantile_elements = te.estimate
      # second call
      quantile_elements = te.estimate
      expexcted_values = [0, 0, 1, 1, 2, 2, 3, 3, 4, 4]
      expexcted = expexcted_values.map{|value| convert_value_from_index(te_index, value)}
      quantile_elements.should == expexcted
    end

    it "return approximate number when the number of elements is greater than quantile_elems" do
      qe = quantile_estimator.new(11)
      elems = (0 .. 1000).to_a.sort_by{rand}
      elems.each do |elem|
        qe.add_elem(convert_value_from_index(te_index, elem))
      end
      quantiles = qe.estimate
      quantiles.length.should == 11
      quantiles.each_with_index do |tile, index|
        exact = index * 100
        diff = (tile - exact).abs
        diff.should < 10
      end
    end
    
  end
end

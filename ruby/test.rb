require "szaru"

def test_unique
  ue = SZaru::UniqueEstimator.new(4)
  1000.times do |i|
    ue.add_elem(i.to_s + "test")
  end
  1000.times do |i|
    ue.add_elem(i.to_s + "hoge")
  end
  puts ue.estimate
end


def test_topheap
  th = SZaru::TopHeap.new(3)
  th.add_new_elem("test", 45.0)
  th.add_new_elem("test1", 3.0)
  th.add_new_elem("test2", 2.4)
  th.add_new_elem("test3", 4.0)
  th.add_new_elem("test4", 9.1)
  p th.smallest
end

test_topheap

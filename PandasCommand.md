Get a list of unique elements in a give columns
  data[data['sample_names'].duplicated() == False]

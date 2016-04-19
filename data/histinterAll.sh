for ii in mass_plots_rebinned_2012_MVAlike.root
  do
  root -l -b -q "histinter.C(\"${ii}\")"
done

$sizes =  256, 512, 1024
$channels = 3, 16, 32, 64, 128
$threads = 2, 4, 8, 16, 32, 64, 128
$runs = 50

$filename = "risultati_par_opz1.csv"
"Size,Channels,Threads,Time_s" | Out-File -FilePath $filename -Encoding ascii

foreach ($s in $sizes) {
    foreach ($c in $channels) {
        foreach($t in $threads){
        Write-Host "Test: Dim=$s, Canali=$c, Threads=$t"
        
        .\dwconv_par.exe $s $c $runs $t | Out-File -FilePath $filename -Append -Encoding ascii
        
    }
    }
}
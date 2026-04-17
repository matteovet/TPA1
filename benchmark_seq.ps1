$sizes =  256, 512, 1024
$channels = 3, 16, 32, 64, 128
$runs = 50

$filename = "risultati_seq_loopchange.csv"

"Size,Channels, Thread, Time_s" | Out-File -FilePath $filename -Encoding ascii

foreach ($s in $sizes) {
    foreach ($c in $channels) {
    
        Write-Host "Test: Dim=$s, Canali=$c"
        
        .\dwconv_seq.exe $s $c $runs | Out-File -FilePath $filename -Append -Encoding ascii
    
    }
}
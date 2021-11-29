# 1
Για να δούμε τις βασικές παραμέτρους του συστήματος που προσομοιώθηκε πρέπει να ψάξουμε στο αρχείο config.ini . Οι βασικές παράμετροι του συτήματος είναι 

- *Τύπος CPU* : MinorCPU. Μοντέλο in-order επεξεργαστή με μεταβλητά data structures και συμπεριφορές εκτέλεσης. (system.cpu_cluster.cpus.type = MinorCPU)
- *Συχνότητα λειτουργείας*: 1GHz (system.clk_domain.clock=1000, root.time_sync_period=100000000000)
-*Μνήμη*: Μέγεθος γραμμής cache 64 bits(system.cache_line_size=64).
H συχνότητα της CPU μπορεί να επιλεγεί με τη χρήση της εντολής --cpu-freq
 > Πράγμα που φαίνεται στο documentation αλλά εμείς στην πράξη δεν είδαμε εξετάζοντας τα αρχεία config.ini και stats.txt

# 2
Διαβάζοντας το stats.txt :
sim_insts                                        5028   
sim_seconds                                  0.000020  
host_inst_rate                                  90823                       Όπου sim_insts  είναι ο αριθμός των εντολών που προσομοιώθηκαν, sim_seconds η διάρκεια του προγράμματος (σε προσομοιωμένα δευτερόλεπτα) και host_inst_rate  ο ρυθμός εκτέλεσης εντολών από τον υπολογιστή 

# 3
Ψάχνοντας στο config.ini για τα IL1.n_m, DL1.n_m, IL2.n_m, n_i
όπου n_m: miss number, n_i: Total instruction number βρήκαμε:

DL1 miss rate= 0.084298   
(system.cpu_cluster.cpus.dcache.overall_miss_rate::total     0.084298)

-IL1 miss rate =0.119795 
(system.cpu_cluster.cpus.icache.overall_miss_rate::total     0.119795 )
     
-IL2 miss rate = 1
(system.cpu_cluster.l2.demand_miss_rate::total            1   ) 


$$
CPI=1+ ( (IL1.r_m  +  DL1.n_m ) *6  + IL2.r_m*50) =52.22
$$
όπου r_m: miss rate 

> DL1 miss number= 182, L1 miss number =328, IL2 miss nuber = 475, **CPI=6.33** με την χρήση των overall misses και simulated instructions

# 4

## Minor
Το Minor είναι ένα in-order μοντέλο επεξεργαστή με data structures και συμπεριφορές εκτέλεσης.  Επιλέγεται για την καθαρή συσχέτιση ανάλογων μοντέλων σε επίπεδο μικροαρχιτεκτινικής. Δεν υποστηρίζει multi-threading.


## SimpleCPU


Το SimpleCPU είναι ένα μοντέλο που χρησιμοποιείται όταν η εφαρμογή δεν χρειάζεται συγκεκριμένο μοντέλο και χρειάζεται να ελεγχθεί ένα πρόγραμμα, πχ. σε περίοδο testing. Χωρίζεται σε 3 κλάσσεις: 
- BaseSimpleCPU: Κρατά την αρχιτεκτονική και στατιστικά ανάλογα με το μοντέλο, καθώς δεν μπορεί να εφαρμοστεί απο μόνη της σαν κλάσση, χρειάζεται και ένα από τα παρακάτω. Επίσης δημιουργεί συναρτήσεις interupt και άλλες κοινές συναρτήσεις των SimpleCPUs. 
- AtomicSimpleCPU: Χρησιμοποιείται για την παρακολούθηση της πόσβασης στη μνήμη. 
- TimingSimpleCPU: Καθυστερεί στην πρόσβαση στην cache και περιμένει για απάντηση από τη μήμη για να συνεχίσει.

## a
Επιλέχθηκε η υλοποίηση προγράμματος προβολής της ακολουθίας Fibonacci. Όπως φαίνεται και από τα παρακάτω αποτελέσματα ο τύπος MinorCPU ήταν πιο γρήγορος από τον τύπο TimingSimpleCPU στην προσομοίωση αυτού του προγράμματος.

**Timing simple CPU**
host_seconds                                     0.13    
>real time elapsed on the host

sim_insts                                       27943
>Number of instructions simulated

sim_ops                                         32208                       
>Number of ops (including micro ops) simulated

sim_seconds                                  0.002055                       
>Number of seconds simulated

sim_ticks                                  2055324000                       
> Number of ticks simulated

**Minor**
host_seconds                                     0.13                       
>Real time elapsed on the host

sim_insts                                       28120                       
> Number of instructions simulated 
>
sim_ops                                         32560                       
> Number of ops (including micro ops) simulated
> 
sim_seconds                                  0.000048                       
>Number of seconds simulated

sim_ticks                                    48411000                       
>Number of ticks simulated

## b
### i
> Όμοια με την άσκηση 1 δεν μπορέσαμε να διακρίνουμε κάποια διαφορά στο stats.txt αλλάζοντας την συχνότητα
### ii

Timing Simple 
	DDR3: sim_sec: 0,002055
	DDR5: sim _sec:0,003064


Minor 
	DDR3: sim_sec: 0,000048
	DDR5: sim _sec:0,000061

Το Timing Simple μοντέλο καθυστερεί περισσότερο από το Minor και ο χρόνος απόκρισης έχει μεγαλύτερη διαφορά ανάμεσα σε τεχνολογίες λόγω της αναμονής απόκρισης μνήμης που έχει πριν την πρόσβασή της, πράγμα που επηρεάζεται από την τεχνολογία της μνήμης που επιλέγεται κάθε φορά.




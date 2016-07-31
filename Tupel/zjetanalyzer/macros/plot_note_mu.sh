ismu=1
declare -a arr=(
inc_ljet_Z_y_0
inc_ljet_Z_y_1
inc_ljet_Z_y_2
inc_ljet_Z_y_3
inc_ljet_Z_y_4
inc_ljet_Z_y_5
inc_ljet_Z_y_6
inc_ljet_pt_y_fb_pos_z0_0
inc_ljet_pt_y_fb_pos_z0_1
inc_ljet_pt_y_fb_pos_z0_2
inc_ljet_pt_y_fb_pos_z1_0
inc_ljet_pt_y_fb_pos_z1_1
inc_ljet_pt_y_fb_pos_z1_2
inc_ljet_pt_y_fb_neg_z0_0
inc_ljet_pt_y_fb_neg_z0_1
inc_ljet_pt_y_fb_neg_z0_2
inc_ljet_pt_y_fb_neg_z1_0
inc_ljet_pt_y_fb_neg_z1_1
inc_ljet_pt_y_fb_neg_z1_2
mjjjj
n_jet_30_unfold
MZ
Zpt
Zrapidity
Zphi
ljet_rapidity
ljet_eta
sljet_rapidity
sljet_eta
nvtx
jetpt_1
jetpt_2
jetY_1
jetY_2
lpt
leta
lphi
inc_ljet_pt_y_fb_0
inc_ljet_pt_y_fb_1
inc_ljet_pt_y_fb_2
inc_ljet_pt_y_fb_3
inc_ljet_pt_y_fb_4
inc_ljet_pt_y_fb_5
inc_ljet_pt_y_fb_6
inc_ljet_pt_y_fb_z0_0
inc_ljet_pt_y_fb_z0_1
inc_ljet_pt_y_fb_z0_2
inc_ljet_pt_y_fb_z0_3
inc_ljet_pt_y_fb_z0_4
inc_ljet_pt_y_fb_z0_5
inc_ljet_pt_y_fb_z0_6
inc_ljet_pt_y_fb_z1_0
inc_ljet_pt_y_fb_z1_1
inc_ljet_pt_y_fb_z1_2
inc_ljet_pt_y_fb_z1_3
inc_ljet_pt_y_fb_z1_4
inc_ljet_pt_y_fb_z1_5
inc_ljet_pt_y_fb_z1_6
inc_ljet_pt_y_fb_alljetrap_pos_z0
inc_ljet_pt_y_fb_alljetrap_pos_z0
inc_ljet_pt_y_fb_alljetrap_neg_z1
inc_ljet_pt_y_fb_alljetrap_neg_z1
)
declare -a title=(
"y(Z)*sgn(y(j)) ( 0.0<|Y(j)|<0.5)"
"y(Z)*sgn(y(j)) (0.5<|Y(j)|<1.0)"
"y(Z)*sgn(y(j)) (1.0<|Y(j)|<1.5)"
"y(Z)*sgn(y(j)) (1.5<|Y(j)|<2.0)"
"y(Z)*sgn(y(j)) (2.0<|Y(j)|<2.5)"
"y(Z)*sgn(y(j)) (2.5<|Y(j)|<3.2)"
"y(Z)*sgn(y(j)) (3.2<|Y(j)|<4.7)"

"P_{T}(j) (|Y(Z)|<1.0, 0.0<|Y(j)|<1.5,Y(j)*Y(Z)>0)"
"P_{T}(j) (|Y(Z)|<1.0,1.5<|Y(j)|<2.5,Y(j)*Y(Z)>0)"
"P_{T}(j) (|Y(Z)|<1.0,2.5<|Y(j)|<4.7,Y(j)*Y(Z)>0)"

"P_{T}(j) (|Y(Z)|>1.0, 0.0<|Y(j)|<1.5,Y(j)*Y(Z)>0)"
"P_{T}(j) (|Y(Z)|>1.0,1.5<|Y(j)|<2.5,Y(j)*Y(Z)>0)"
"P_{T}(j) (|Y(Z)|>1.0,2.5<|Y(j)|<4.7,Y(j)*Y(Z)>0)"

"P_{T}(j) (|Y(Z)|<1.0, 0.0<|Y(j)|<1.5,Y(j)*Y(Z)<0)"
"P_{T}(j) (|Y(Z)|<1.0,1.5<|Y(j)|<2.5,Y(j)*Y(Z)<0)"
"P_{T}(j) (|Y(Z)|<1.0,2.5<|Y(j)|<4.7,Y(j)*Y(Z)<0)"

"P_{T}(j) (|Y(Z)|>1.0, 0.0<|Y(j)|<1.5,Y(j)*Y(Z)<0)"
"P_{T}(j) (|Y(Z)|>1.0,1.5<|Y(j)|<2.5,Y(j)*Y(Z)<0)"
"P_{T}(j) (|Y(Z)|>1.0,2.5<|Y(j)|<4.7,Y(j)*Y(Z)<0)"
"M(jjjj)"
"N_{jet}"
"M_{#mu#mu}[GeV]"
"P_{T}^{#mu#mu}[GeV]"
"Y_{#mu#mu}"
"#phi_{#mu#mu}"
"ljet_rapidity"
"ljet_eta"
"sljet_rapidity"
"sljet_eta"
"nvtx"
"P_{T}^{jet}[GeV]"
"P_{T}^{jet}[GeV]"
"y_{jet}"
"y_{jet}"
"P_{T}^{#mu}[GeV]"
"y_{#mu}"
"#phi_{#mu}"
"P_{T}(j) ( 0.0<|Y(j)|<0.5)"
"P_{T}(j) (0.5<|Y(j)|<1.0)"
"P_{T}(j) (1.0<|Y(j)|<1.5)"
"P_{T}(j) (1.5<|Y(j)|<2.0)"
"P_{T}(j) (2.0<|Y(j)|<2.5)"
"P_{T}(j) (2.5<|Y(j)|<3.2)"
"P_{T}(j) (3.2<|Y(j)|<4.7)"
"P_{T}(j) (|Y(Z)|<1.0, 0.0<|Y(j)|<0.5)"
"P_{T}(j) (|Y(Z)|<1.0,0.5<|Y(j)|<1.0)"
"P_{T}(j) (|Y(Z)|<1.0,1.0<|Y(j)|<1.5)"
"P_{T}(j) (|Y(Z)|<1.0,1.5<|Y(j)|<2.0)"
"P_{T}(j) (|Y(Z)|<1.0,2.0<|Y(j)|<2.5)"
"P_{T}(j) (|Y(Z)|<1.0,2.5<|Y(j)|<3.2)"
"P_{T}(j) (|Y(Z)|<1.0,3.2<|Y(j)|<4.7)"
"P_{T}(j) (|Y(Z)|>1.0, 0.0<|Y(j)|<0.5)"
"P_{T}(j) (|Y(Z)|>1.0,0.5<|Y(j)|<1.0)"
"P_{T}(j) (|Y(Z)|>1.0,1.0<|Y(j)|<1.5)"
"P_{T}(j) (|Y(Z)|>1.0,1.5<|Y(j)|<2.0)"
"P_{T}(j) (|Y(Z)|>1.0,2.0<|Y(j)|<2.5)"
"P_{T}(j) (|Y(Z)|>1.0,2.5<|Y(j)|<3.2)"
"P_{T}(j) (|Y(Z)|>1.0,3.2<|Y(j)|<4.7)"
"P_{T}(j) (|Y(Z)|<1.0,,Y(j)*Y(Z)>0)"
"P_{T}(j) (1.0<|Y(Z)|<2.5,,Y(j)*Y(Z)>0)"
"P_{T}(j) (|Y(Z)|<1.0,,Y(j)*Y(Z)<0)"
"P_{T}(j) (1.0<|Y(Z)|<2.5,,Y(j)*Y(Z)<0)"
)


for ((n =0 ; n<${#arr[@]} ;n++ ))
do

                echo "${arr[$n]}"
                echo "${title[$n]}"
                cat plot_note.C | sed "s/__HISTNAME__/${arr[$n]}/g
					s/__ISMU__/$ismu/g"> macro_tmp2.C 
if [ $n == 3 ] || [ $n == 0 ] || [ $n == 15 ] ; then
		cat macro_tmp2.C | sed "s/__NBIN__/1/g"> macro_tmp3.C
		cat macro_tmp3.C | sed "s/__TITLE__/${title[$n]}/g"> macro_tmp.C
else 

	                     cat macro_tmp2.C | sed "s/__NBIN__/1/g"> macro_tmp3.C
                             cat macro_tmp3.C | sed "s/__TITLE__/${title[$n]}/g"> macro_tmp.C		
       
fi
		root -l -q macro_tmp.C 

rm macro_tmp2.C
rm macro_tmp3.C
#rm macro_tmp.C
done

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "gen_exported.h"

namespace C74_GENPLUGIN {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_36;
	Delay m_delay_2;
	Delay m_delay_1;
	Phasor __m_phasor_76;
	Phasor __m_phasor_72;
	Phasor __m_phasor_73;
	Phasor __m_phasor_77;
	Phasor __m_phasor_75;
	Phasor __m_phasor_74;
	PlusEquals __m_pluseq_37;
	PlusEquals __m_pluseq_45;
	Sah __m_sah_38;
	SineCycle __m_cycle_79;
	SineCycle __m_cycle_29;
	SineCycle __m_cycle_78;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_z_105;
	t_sample __m_carry_90;
	t_sample m_z_106;
	t_sample m_z_104;
	t_sample samples_to_seconds;
	t_sample __m_slide_69;
	t_sample m_y_103;
	t_sample __m_slide_66;
	t_sample __m_slide_60;
	t_sample __m_latch_53;
	t_sample __m_slide_63;
	t_sample __m_slide_54;
	t_sample __m_slide_57;
	t_sample __m_latch_92;
	t_sample m_mf_102;
	t_sample m_z_99;
	t_sample __m_count_83;
	t_sample __m_slide_80;
	t_sample __m_carry_85;
	t_sample __m_count_88;
	t_sample __m_latch_87;
	t_sample m_z_100;
	t_sample __m_latch_52;
	t_sample m_y_95;
	t_sample m_z_98;
	t_sample m_mf_94;
	t_sample m_z_97;
	t_sample m_z_96;
	t_sample __m_latch_51;
	t_sample __m_latch_47;
	t_sample __m_latch_49;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample m_history_10;
	t_sample m_OscFourVol_13;
	t_sample m_DelayLFO_15;
	t_sample m_ReDux_14;
	t_sample m_OscThreeVol_16;
	t_sample m_OscFiveVol_17;
	t_sample m_history_9;
	t_sample m_history_7;
	t_sample m_history_3;
	t_sample samplerate;
	t_sample m_history_8;
	t_sample m_history_4;
	t_sample m_history_6;
	t_sample m_history_5;
	t_sample __m_latch_50;
	t_sample m_GateLevel_18;
	t_sample m_OscOneVol_20;
	t_sample __m_slide_39;
	t_sample __m_slide_33;
	t_sample __m_slide_30;
	t_sample __m_slide_42;
	t_sample m_z_107;
	t_sample __m_latch_46;
	t_sample __m_latch_48;
	t_sample m_Freeze_19;
	t_sample m_FilterCutOff_28;
	t_sample m_AM_26;
	t_sample m_OscSixVol_22;
	t_sample m_OscTwoVol_21;
	t_sample m_Spread_27;
	t_sample m_FilterQ_23;
	t_sample m_Bitcrush_25;
	t_sample m_Volume_24;
	t_sample m_z_108;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)1500));
		m_delay_2.reset("m_delay_2", ((int)2000));
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_OscFourVol_13 = 6;
		m_ReDux_14 = 1.25;
		m_DelayLFO_15 = 20;
		m_OscThreeVol_16 = 6;
		m_OscFiveVol_17 = 6;
		m_GateLevel_18 = -70;
		m_Freeze_19 = 1;
		m_OscOneVol_20 = 6;
		m_OscTwoVol_21 = 6;
		m_OscSixVol_22 = 6;
		m_FilterQ_23 = 0;
		m_Volume_24 = 6;
		m_Bitcrush_25 = 16;
		m_AM_26 = 1;
		m_Spread_27 = 0;
		m_FilterCutOff_28 = 15000;
		__m_cycle_29.reset(samplerate, 0);
		__m_slide_30 = 0;
		__m_slide_33 = 0;
		__m_change_36.reset(0);
		__m_pluseq_37.reset(0);
		__m_sah_38.reset(44100);
		__m_slide_39 = 0;
		__m_slide_42 = 0;
		__m_pluseq_45.reset(0);
		__m_latch_46 = 0;
		__m_latch_47 = 0;
		__m_latch_48 = 0;
		__m_latch_49 = 0;
		__m_latch_50 = 0;
		__m_latch_51 = 0;
		__m_latch_52 = 0;
		__m_latch_53 = 0;
		__m_slide_54 = 0;
		__m_slide_57 = 0;
		__m_slide_60 = 0;
		__m_slide_63 = 0;
		__m_slide_66 = 0;
		__m_slide_69 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_72.reset(0);
		__m_phasor_73.reset(0);
		__m_phasor_74.reset(0);
		__m_phasor_75.reset(0);
		__m_phasor_76.reset(0);
		__m_phasor_77.reset(0);
		__m_cycle_78.reset(samplerate, 0);
		__m_cycle_79.reset(samplerate, 0);
		__m_slide_80 = 0;
		__m_count_83 = 0;
		__m_carry_85 = 0;
		__m_latch_87 = 0;
		__m_count_88 = 0;
		__m_carry_90 = 0;
		__m_latch_92 = 0;
		m_mf_94 = ((int)0);
		m_y_95 = ((int)0);
		m_z_96 = ((int)0);
		m_z_97 = ((int)0);
		m_z_98 = ((int)0);
		m_z_99 = ((int)0);
		m_z_100 = ((int)0);
		m_mf_102 = ((int)0);
		m_y_103 = ((int)0);
		m_z_104 = ((int)0);
		m_z_105 = ((int)0);
		m_z_106 = ((int)0);
		m_z_107 = ((int)0);
		m_z_108 = ((int)0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample dbtoa_213 = dbtoa(m_GateLevel_18);
		t_sample dbtoa_215 = dbtoa(m_Volume_24);
		t_sample iup_31 = (1 / maximum(1, abs(((int)10))));
		t_sample idown_32 = (1 / maximum(1, abs(((int)10))));
		t_sample iup_34 = (1 / maximum(1, abs(((int)10))));
		t_sample idown_35 = (1 / maximum(1, abs(((int)10))));
		t_sample omega = safediv(((t_sample)9424.7779607694), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)10));
		t_sample b0 = safediv(((int)1), (((int)1) + alpha));
		t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
		t_sample a1 = ((((int)1) - cs) * b0);
		t_sample b1 = ((((int)-2) * cs) * b0);
		t_sample b2 = ((((int)1) - alpha) * b0);
		t_sample expr_200 = a2;
		t_sample expr_201 = a1;
		t_sample expr_202 = a2;
		t_sample expr_203 = b1;
		t_sample expr_204 = b2;
		t_sample omega_248 = safediv(((t_sample)251.32741228718), samplerate);
		t_sample sn_251 = sin(omega_248);
		t_sample cs_247 = cos(omega_248);
		t_sample alpha_252 = ((sn_251 * ((t_sample)0.5)) * ((t_sample)10));
		t_sample b_244 = safediv(((int)1), (((int)1) + alpha_252));
		t_sample a_245 = (((((int)1) + cs_247) * ((t_sample)0.5)) * b_244);
		t_sample a_250 = ((-(((int)1) + cs_247)) * b_244);
		t_sample b_249 = ((((int)-2) * cs_247) * b_244);
		t_sample b_246 = ((((int)1) - alpha_252) * b_244);
		t_sample expr_170 = a_245;
		t_sample expr_171 = a_250;
		t_sample expr_172 = a_245;
		t_sample expr_173 = b_249;
		t_sample expr_174 = b_246;
		t_sample mstosamps_131 = (((int)1) * (samplerate * 0.001));
		t_sample iup_40 = (1 / maximum(1, abs(mstosamps_131)));
		t_sample idown_41 = (1 / maximum(1, abs(mstosamps_131)));
		t_sample iup_43 = (1 / maximum(1, abs(((int)1))));
		t_sample idown_44 = (1 / maximum(1, abs(((int)1))));
		t_sample dbtoa_226 = dbtoa(m_OscOneVol_20);
		t_sample dbtoa_225 = dbtoa(m_OscTwoVol_21);
		t_sample dbtoa_224 = dbtoa(m_OscThreeVol_16);
		t_sample dbtoa_223 = dbtoa(m_OscFourVol_13);
		t_sample dbtoa_222 = dbtoa(m_OscFiveVol_17);
		t_sample dbtoa_221 = dbtoa(m_OscSixVol_22);
		t_sample iup_55 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_56 = (1 / maximum(1, abs(((int)1000))));
		t_sample iup_58 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_59 = (1 / maximum(1, abs(((int)1000))));
		t_sample iup_61 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_62 = (1 / maximum(1, abs(((int)1000))));
		t_sample iup_64 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_65 = (1 / maximum(1, abs(((int)1000))));
		t_sample iup_67 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_68 = (1 / maximum(1, abs(((int)1000))));
		t_sample iup_70 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_71 = (1 / maximum(1, abs(((int)1000))));
		t_sample mul_74 = (m_Spread_27 * ((int)3));
		t_sample mul_73 = (m_Spread_27 * ((int)4));
		t_sample mul_72 = (m_Spread_27 * ((int)5));
		t_sample mul_75 = (m_Spread_27 * ((int)2));
		samples_to_seconds = (1 / samplerate);
		t_sample SamplingValue = m_ReDux_14;
		t_sample pow_21 = safepow(((int)2), m_Bitcrush_25);
		t_sample mul_9 = (pow_21 * ((int)1));
		t_sample pow_11 = safepow(((int)2), m_Bitcrush_25);
		t_sample mul_8 = (pow_11 * ((int)1));
		t_sample iup_81 = (1 / maximum(1, abs(((int)10000))));
		t_sample idown_82 = (1 / maximum(1, abs(((int)10000))));
		t_sample max_93 = (samplerate * ((t_sample)0.25));
		t_sample Cutoff = ((m_FilterCutOff_28 <= ((int)20)) ? ((int)20) : ((m_FilterCutOff_28 >= max_93) ? max_93 : m_FilterCutOff_28));
		t_sample Res = ((m_FilterQ_23 <= ((int)0)) ? ((int)0) : ((m_FilterQ_23 >= ((int)1)) ? ((int)1) : m_FilterQ_23));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample expr_240 = ((int)0);
			t_sample expr_241 = ((int)0);
			t_sample expr_238 = ((int)0);
			t_sample expr_242 = ((int)0);
			t_sample expr_237 = ((int)0);
			t_sample expr_239 = ((int)0);
			t_sample expr_236 = ((int)0);
			t_sample expr_243 = ((int)0);
			if ((in1 > dbtoa_213)) {
				expr_243 = in1;
				
			} else {
				expr_243 = ((int)0);
				
			};
			__m_cycle_29.freq(m_AM_26);
			t_sample cycle_219 = __m_cycle_29(__sinedata);
			t_sample cycleindex_220 = __m_cycle_29.phase();
			if ((cycle_219 == ((int)0))) {
				expr_236 = ((int)1);
				
			} else {
				expr_236 = cycle_219;
				
			};
			__m_slide_30 = fixdenorm((__m_slide_30 + (((dbtoa_215 > __m_slide_30) ? iup_31 : idown_32) * (dbtoa_215 - __m_slide_30))));
			t_sample slide_214 = __m_slide_30;
			__m_slide_33 = fixdenorm((__m_slide_33 + (((expr_243 > __m_slide_33) ? iup_34 : idown_35) * (expr_243 - __m_slide_33))));
			t_sample slide_227 = __m_slide_33;
			t_sample mul_194 = (slide_227 * expr_200);
			t_sample mul_191 = (m_history_10 * expr_201);
			t_sample mul_189 = (m_history_11 * expr_202);
			t_sample mul_185 = (m_history_12 * expr_204);
			t_sample mul_187 = (m_history_9 * expr_203);
			t_sample sub_193 = (((mul_189 + mul_191) + mul_194) - (mul_187 + mul_185));
			t_sample gen_199 = sub_193;
			t_sample history_186_next_195 = fixdenorm(m_history_9);
			t_sample history_190_next_196 = fixdenorm(m_history_10);
			t_sample history_192_next_197 = fixdenorm(slide_227);
			t_sample history_188_next_198 = fixdenorm(sub_193);
			t_sample gen_205 = gen_199;
			t_sample mul_164 = (gen_205 * expr_170);
			t_sample mul_161 = (m_history_6 * expr_171);
			t_sample mul_159 = (m_history_7 * expr_172);
			t_sample mul_155 = (m_history_8 * expr_174);
			t_sample mul_157 = (m_history_5 * expr_173);
			t_sample sub_163 = (((mul_159 + mul_161) + mul_164) - (mul_157 + mul_155));
			t_sample gen_169 = sub_163;
			t_sample history_156_next_165 = fixdenorm(m_history_5);
			t_sample history_160_next_166 = fixdenorm(m_history_6);
			t_sample history_162_next_167 = fixdenorm(gen_205);
			t_sample history_158_next_168 = fixdenorm(sub_163);
			t_sample gen_175 = gen_169;
			t_sample mul_1 = (gen_175 * ((t_sample)2.7));
			t_sample FilteredMicrophone_145 = mul_1;
			int gt_140 = (FilteredMicrophone_145 > ((int)0));
			int change_139 = __m_change_36(gt_140);
			int gt_138 = (change_139 > ((int)0));
			int plusequals_137 = __m_pluseq_37.post(((int)1), gt_138, 0);
			t_sample sah_136 = __m_sah_38(m_history_3, gt_138, ((int)0));
			t_sample rdiv_134 = safediv(samplerate, sah_136);
			__m_slide_39 = fixdenorm((__m_slide_39 + (((rdiv_134 > __m_slide_39) ? iup_40 : idown_41) * (rdiv_134 - __m_slide_39))));
			t_sample slide_133 = __m_slide_39;
			__m_slide_42 = fixdenorm((__m_slide_42 + (((FilteredMicrophone_145 > __m_slide_42) ? iup_43 : idown_44) * (FilteredMicrophone_145 - __m_slide_42))));
			t_sample slide_124 = __m_slide_42;
			t_sample mul_130 = (slide_124 * slide_124);
			t_sample plusequals_129 = __m_pluseq_45.post(mul_130, m_history_4, 0);
			__m_latch_46 = ((gt_138 != 0) ? plusequals_129 : __m_latch_46);
			t_sample latch_128 = __m_latch_46;
			t_sample div_126 = safediv(latch_128, sah_136);
			t_sample sqrt_125 = sqrt(div_126);
			t_sample gen_144 = sqrt_125;
			t_sample history_127_next_141 = fixdenorm(gt_138);
			t_sample history_135_next_142 = fixdenorm(plusequals_137);
			if ((gen_144 > ((int)0))) {
				expr_237 = gen_144;
				
			};
			if ((gen_144 > ((t_sample)0.05))) {
				expr_238 = gen_144;
				
			};
			if ((gen_144 > ((t_sample)0.1))) {
				expr_239 = gen_144;
				
			};
			if ((gen_144 > ((t_sample)0.15))) {
				expr_240 = gen_144;
				
			};
			if ((gen_144 > ((t_sample)0.2))) {
				expr_241 = gen_144;
				
			};
			if ((gen_144 > ((t_sample)0.22))) {
				expr_242 = gen_144;
				
			};
			t_sample rsub_235 = (((int)1) - gen_144);
			__m_latch_47 = ((m_Freeze_19 != 0) ? expr_237 : __m_latch_47);
			t_sample latch_116 = __m_latch_47;
			__m_latch_48 = ((m_Freeze_19 != 0) ? expr_240 : __m_latch_48);
			t_sample latch_114 = __m_latch_48;
			__m_latch_49 = ((m_Freeze_19 != 0) ? slide_133 : __m_latch_49);
			t_sample latch_111 = __m_latch_49;
			__m_latch_50 = ((m_Freeze_19 != 0) ? expr_238 : __m_latch_50);
			t_sample latch_115 = __m_latch_50;
			__m_latch_51 = ((m_Freeze_19 != 0) ? expr_241 : __m_latch_51);
			t_sample latch_113 = __m_latch_51;
			__m_latch_52 = ((m_Freeze_19 != 0) ? expr_239 : __m_latch_52);
			t_sample latch_110 = __m_latch_52;
			__m_latch_53 = ((m_Freeze_19 != 0) ? expr_242 : __m_latch_53);
			t_sample latch_112 = __m_latch_53;
			t_sample mul_81 = (latch_116 * dbtoa_226);
			__m_slide_54 = fixdenorm((__m_slide_54 + (((mul_81 > __m_slide_54) ? iup_55 : idown_56) * (mul_81 - __m_slide_54))));
			t_sample slide_89 = __m_slide_54;
			t_sample mul_78 = (latch_114 * dbtoa_223);
			__m_slide_57 = fixdenorm((__m_slide_57 + (((mul_78 > __m_slide_57) ? iup_58 : idown_59) * (mul_78 - __m_slide_57))));
			t_sample slide_98 = __m_slide_57;
			t_sample mul_77 = (latch_113 * dbtoa_222);
			__m_slide_60 = fixdenorm((__m_slide_60 + (((mul_77 > __m_slide_60) ? iup_61 : idown_62) * (mul_77 - __m_slide_60))));
			t_sample slide_95 = __m_slide_60;
			t_sample mul_76 = (latch_112 * dbtoa_221);
			__m_slide_63 = fixdenorm((__m_slide_63 + (((mul_76 > __m_slide_63) ? iup_64 : idown_65) * (mul_76 - __m_slide_63))));
			t_sample slide_92 = __m_slide_63;
			t_sample mul_80 = (latch_115 * dbtoa_225);
			__m_slide_66 = fixdenorm((__m_slide_66 + (((mul_80 > __m_slide_66) ? iup_67 : idown_68) * (mul_80 - __m_slide_66))));
			t_sample slide_90 = __m_slide_66;
			t_sample mul_79 = (latch_110 * dbtoa_224);
			__m_slide_69 = fixdenorm((__m_slide_69 + (((mul_79 > __m_slide_69) ? iup_70 : idown_71) * (mul_79 - __m_slide_69))));
			t_sample slide_102 = __m_slide_69;
			t_sample phasor_108 = __m_phasor_72(latch_111, samples_to_seconds);
			t_sample mul_71 = (phasor_108 * ((int)2));
			t_sample sub_70 = (mul_71 - ((int)1));
			t_sample mul_107 = (sub_70 * slide_89);
			t_sample mul_94 = (latch_111 * mul_73);
			t_sample phasor_62 = __m_phasor_73(mul_94, samples_to_seconds);
			t_sample mul_61 = (phasor_62 * ((int)2));
			t_sample sub_60 = (mul_61 - ((int)1));
			t_sample mul_96 = (sub_60 * slide_95);
			t_sample mul_97 = (latch_111 * mul_74);
			t_sample phasor_65 = __m_phasor_74(mul_97, samples_to_seconds);
			t_sample mul_64 = (phasor_65 * ((int)2));
			t_sample sub_63 = (mul_64 - ((int)1));
			t_sample mul_99 = (sub_63 * slide_98);
			t_sample mul_91 = (latch_111 * mul_72);
			t_sample phasor_59 = __m_phasor_75(mul_91, samples_to_seconds);
			t_sample mul_58 = (phasor_59 * ((int)2));
			t_sample sub_57 = (mul_58 - ((int)1));
			t_sample mul_93 = (sub_57 * slide_92);
			t_sample mul_104 = (latch_111 * m_Spread_27);
			t_sample phasor_106 = __m_phasor_76(mul_104, samples_to_seconds);
			t_sample mul_69 = (phasor_106 * ((int)2));
			t_sample sub_68 = (mul_69 - ((int)1));
			t_sample mul_105 = (sub_68 * slide_90);
			t_sample mul_100 = (latch_111 * mul_75);
			t_sample phasor_101 = __m_phasor_77(mul_100, samples_to_seconds);
			t_sample mul_67 = (phasor_101 * ((int)2));
			t_sample sub_66 = (mul_67 - ((int)1));
			t_sample mul_103 = (sub_66 * slide_102);
			t_sample output_82 = (((((mul_103 + mul_105) + mul_93) + mul_96) + mul_99) + mul_107);
			t_sample mul_218 = (output_82 * expr_236);
			t_sample mul_40 = (rsub_235 * ((t_sample)0.5));
			__m_cycle_78.freq(((int)1));
			t_sample cycle_47 = __m_cycle_78(__sinedata);
			t_sample cycleindex_48 = __m_cycle_78.phase();
			t_sample add_36 = (cycle_47 + ((int)1));
			t_sample mul_35 = (add_36 * (-1));
			t_sample mul_46 = (mul_35 * m_DelayLFO_15);
			t_sample add_37 = (mul_46 + ((int)1000));
			t_sample tap_54 = m_delay_2.read_linear(add_37);
			t_sample mix_253 = (mul_218 + (mul_40 * (tap_54 - mul_218)));
			t_sample mul_50 = (tap_54 * ((t_sample)0.6));
			__m_cycle_79.freq(((int)1));
			t_sample cycle_44 = __m_cycle_79(__sinedata);
			t_sample cycleindex_45 = __m_cycle_79.phase();
			t_sample add_34 = (cycle_44 + ((int)1));
			t_sample mul_33 = (add_34 * (-1));
			t_sample mul_43 = (mul_33 * m_DelayLFO_15);
			t_sample add_38 = (mul_43 + ((int)1200));
			t_sample tap_52 = m_delay_1.read_linear(add_38);
			t_sample mix_254 = (mul_218 + (mul_40 * (tap_52 - mul_218)));
			t_sample mul_49 = (tap_52 * ((t_sample)0.6));
			int expr_30 = ((int)0);
			if ((SamplingValue == ((int)1))) {
				expr_30 = ((int)0);
				
			} else {
				expr_30 = ((int)1);
				
			};
			__m_slide_80 = fixdenorm((__m_slide_80 + (((expr_30 > __m_slide_80) ? iup_81 : idown_82) * (expr_30 - __m_slide_80))));
			t_sample slide_4 = __m_slide_80;
			__m_count_83 = (((int)0) ? 0 : (fixdenorm(__m_count_83 + ((int)1))));
			int carry_84 = 0;
			if ((((int)0) != 0)) {
				__m_count_83 = 0;
				__m_carry_85 = 0;
				
			} else if (((m_ReDux_14 > 0) && (__m_count_83 >= m_ReDux_14))) {
				int wraps_86 = (__m_count_83 / m_ReDux_14);
				__m_carry_85 = (__m_carry_85 + wraps_86);
				__m_count_83 = (__m_count_83 - (wraps_86 * m_ReDux_14));
				carry_84 = 1;
				
			};
			int counter_26 = __m_count_83;
			int counter_27 = carry_84;
			int counter_28 = __m_carry_85;
			__m_latch_87 = ((counter_26 != 0) ? mix_253 : __m_latch_87);
			t_sample latch_29 = __m_latch_87;
			t_sample mix_255 = (mix_253 + (slide_4 * (latch_29 - mix_253)));
			t_sample mul_24 = (mix_255 * pow_21);
			t_sample ceil_23 = ceil(mul_24);
			t_sample div_22 = safediv(ceil_23, mul_9);
			__m_count_88 = (((int)0) ? 0 : (fixdenorm(__m_count_88 + ((int)1))));
			int carry_89 = 0;
			if ((((int)0) != 0)) {
				__m_count_88 = 0;
				__m_carry_90 = 0;
				
			} else if (((m_ReDux_14 > 0) && (__m_count_88 >= m_ReDux_14))) {
				int wraps_91 = (__m_count_88 / m_ReDux_14);
				__m_carry_90 = (__m_carry_90 + wraps_91);
				__m_count_88 = (__m_count_88 - (wraps_91 * m_ReDux_14));
				carry_89 = 1;
				
			};
			int counter_16 = __m_count_88;
			int counter_17 = carry_89;
			int counter_18 = __m_carry_90;
			__m_latch_92 = ((counter_16 != 0) ? mix_254 : __m_latch_92);
			t_sample latch_19 = __m_latch_92;
			t_sample mix_256 = (mix_253 + (slide_4 * (latch_19 - mix_253)));
			t_sample mul_14 = (mix_256 * pow_11);
			t_sample ceil_13 = ceil(mul_14);
			t_sample div_12 = safediv(ceil_13, mul_8);
			t_sample expr_209 = moogLadder_d_d_d(div_22, Cutoff, Res);
			t_sample expr_210 = moogLadder_d_d_d_101(div_12, Cutoff, Res);
			t_sample mul_216 = (expr_210 * slide_214);
			t_sample sin_2 = sin(mul_216);
			t_sample out2 = sin_2;
			t_sample mul_217 = (expr_209 * slide_214);
			t_sample sin_3 = sin(mul_217);
			t_sample out1 = sin_3;
			m_history_12 = history_186_next_195;
			m_history_11 = history_190_next_196;
			m_history_10 = history_192_next_197;
			m_history_9 = history_188_next_198;
			m_history_8 = history_156_next_165;
			m_history_7 = history_160_next_166;
			m_history_6 = history_162_next_167;
			m_history_5 = history_158_next_168;
			m_history_4 = history_127_next_141;
			m_history_3 = history_135_next_142;
			m_delay_2.write((mul_49 + mul_218));
			m_delay_1.write((mul_50 + mul_218));
			m_delay_1.step();
			m_delay_2.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_OscFourVol(t_param _value) {
		m_OscFourVol_13 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_ReDux(t_param _value) {
		m_ReDux_14 = (_value < 1 ? 1 : (_value > 1.3 ? 1.3 : _value));
	};
	inline void set_DelayLFO(t_param _value) {
		m_DelayLFO_15 = (_value < 0 ? 0 : (_value > 44100 ? 44100 : _value));
	};
	inline void set_OscThreeVol(t_param _value) {
		m_OscThreeVol_16 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_OscFiveVol(t_param _value) {
		m_OscFiveVol_17 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_GateLevel(t_param _value) {
		m_GateLevel_18 = (_value < -70 ? -70 : (_value > 0 ? 0 : _value));
	};
	inline void set_Freeze(t_param _value) {
		m_Freeze_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_OscOneVol(t_param _value) {
		m_OscOneVol_20 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_OscTwoVol(t_param _value) {
		m_OscTwoVol_21 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_OscSixVol(t_param _value) {
		m_OscSixVol_22 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_FilterQ(t_param _value) {
		m_FilterQ_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_Volume(t_param _value) {
		m_Volume_24 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_Bitcrush(t_param _value) {
		m_Bitcrush_25 = (_value < 0 ? 0 : (_value > 16 ? 16 : _value));
	};
	inline void set_AM(t_param _value) {
		m_AM_26 = (_value < 0 ? 0 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_Spread(t_param _value) {
		m_Spread_27 = (_value < 0 ? 0 : (_value > 4 ? 4 : _value));
	};
	inline void set_FilterCutOff(t_param _value) {
		m_FilterCutOff_28 = (_value < 1000 ? 1000 : (_value > 20000 ? 20000 : _value));
	};
	inline t_sample moogLadder_d_d_d(t_sample asig, t_sample cf, t_sample res) {
		int i2v = ((int)40000);
		t_sample akfc = safediv(cf, (samplerate * ((t_sample)0.5)));
		t_sample akf = safediv(cf, samplerate);
		t_sample fcr = ((((((t_sample)1.873) * safepow(akfc, ((int)3))) + (((t_sample)0.4955) * safepow(akfc, ((int)2)))) - (((t_sample)0.649) * akfc)) + ((t_sample)0.9988));
		t_sample acr = ((((-((t_sample)3.9364)) * safepow(akfc, ((int)2))) + (((t_sample)1.8409) * akfc)) + ((t_sample)0.9968));
		t_sample twovg = (i2v * (((int)1) - exp(((((-((int)2)) * ((t_sample)3.1415926535898)) * fcr) * akf))));
		t_sample y1 = (m_z_100 + (twovg * (tanh(safediv((asig - (((((int)4) * res) * m_mf_94) * acr)), i2v)) - tanh(safediv(m_z_100, i2v)))));
		m_z_100 = y1;
		t_sample y2 = (m_z_99 + (twovg * (tanh(safediv(y1, i2v)) - tanh(safediv(m_z_99, i2v)))));
		m_z_99 = y2;
		t_sample y3 = (m_z_98 + (twovg * (tanh(safediv(y2, i2v)) - tanh(safediv(m_z_98, i2v)))));
		m_z_98 = y3;
		m_y_95 = (m_z_97 + (twovg * (tanh(safediv(y3, i2v)) - tanh(safediv(m_z_97, i2v)))));
		m_z_97 = m_y_95;
		m_mf_94 = ((m_y_95 + m_z_96) * ((t_sample)0.5));
		m_z_96 = m_y_95;
		return m_mf_94;
		
	};
	inline t_sample moogLadder_d_d_d_101(t_sample asig, t_sample cf, t_sample res) {
		int i2v = ((int)40000);
		t_sample akfc = safediv(cf, (samplerate * ((t_sample)0.5)));
		t_sample akf = safediv(cf, samplerate);
		t_sample fcr = ((((((t_sample)1.873) * safepow(akfc, ((int)3))) + (((t_sample)0.4955) * safepow(akfc, ((int)2)))) - (((t_sample)0.649) * akfc)) + ((t_sample)0.9988));
		t_sample acr = ((((-((t_sample)3.9364)) * safepow(akfc, ((int)2))) + (((t_sample)1.8409) * akfc)) + ((t_sample)0.9968));
		t_sample twovg = (i2v * (((int)1) - exp(((((-((int)2)) * ((t_sample)3.1415926535898)) * fcr) * akf))));
		t_sample y1 = (m_z_108 + (twovg * (tanh(safediv((asig - (((((int)4) * res) * m_mf_102) * acr)), i2v)) - tanh(safediv(m_z_108, i2v)))));
		m_z_108 = y1;
		t_sample y2 = (m_z_107 + (twovg * (tanh(safediv(y1, i2v)) - tanh(safediv(m_z_107, i2v)))));
		m_z_107 = y2;
		t_sample y3 = (m_z_106 + (twovg * (tanh(safediv(y2, i2v)) - tanh(safediv(m_z_106, i2v)))));
		m_z_106 = y3;
		m_y_103 = (m_z_105 + (twovg * (tanh(safediv(y3, i2v)) - tanh(safediv(m_z_105, i2v)))));
		m_z_105 = m_y_103;
		m_mf_102 = ((m_y_103 + m_z_104) * ((t_sample)0.5));
		m_z_104 = m_y_103;
		return m_mf_102;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 16; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "InputSignal" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_AM(value); break;
		case 1: self->set_Bitcrush(value); break;
		case 2: self->set_DelayLFO(value); break;
		case 3: self->set_FilterCutOff(value); break;
		case 4: self->set_FilterQ(value); break;
		case 5: self->set_Freeze(value); break;
		case 6: self->set_GateLevel(value); break;
		case 7: self->set_OscFiveVol(value); break;
		case 8: self->set_OscFourVol(value); break;
		case 9: self->set_OscOneVol(value); break;
		case 10: self->set_OscSixVol(value); break;
		case 11: self->set_OscThreeVol(value); break;
		case 12: self->set_OscTwoVol(value); break;
		case 13: self->set_ReDux(value); break;
		case 14: self->set_Spread(value); break;
		case 15: self->set_Volume(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_AM_26; break;
		case 1: *value = self->m_Bitcrush_25; break;
		case 2: *value = self->m_DelayLFO_15; break;
		case 3: *value = self->m_FilterCutOff_28; break;
		case 4: *value = self->m_FilterQ_23; break;
		case 5: *value = self->m_Freeze_19; break;
		case 6: *value = self->m_GateLevel_18; break;
		case 7: *value = self->m_OscFiveVol_17; break;
		case 8: *value = self->m_OscFourVol_13; break;
		case 9: *value = self->m_OscOneVol_20; break;
		case 10: *value = self->m_OscSixVol_22; break;
		case 11: *value = self->m_OscThreeVol_16; break;
		case 12: *value = self->m_OscTwoVol_21; break;
		case 13: *value = self->m_ReDux_14; break;
		case 14: *value = self->m_Spread_27; break;
		case 15: *value = self->m_Volume_24; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(16 * sizeof(ParamInfo));
	self->__commonstate.numparams = 16;
	// initialize parameter 0 ("m_AM_26")
	pi = self->__commonstate.params + 0;
	pi->name = "AM";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_AM_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_Bitcrush_25")
	pi = self->__commonstate.params + 1;
	pi->name = "Bitcrush";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Bitcrush_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 16;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_DelayLFO_15")
	pi = self->__commonstate.params + 2;
	pi->name = "DelayLFO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_DelayLFO_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_FilterCutOff_28")
	pi = self->__commonstate.params + 3;
	pi->name = "FilterCutOff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_FilterCutOff_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_FilterQ_23")
	pi = self->__commonstate.params + 4;
	pi->name = "FilterQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_FilterQ_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_Freeze_19")
	pi = self->__commonstate.params + 5;
	pi->name = "Freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Freeze_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_GateLevel_18")
	pi = self->__commonstate.params + 6;
	pi->name = "GateLevel";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_GateLevel_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_OscFiveVol_17")
	pi = self->__commonstate.params + 7;
	pi->name = "OscFiveVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscFiveVol_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_OscFourVol_13")
	pi = self->__commonstate.params + 8;
	pi->name = "OscFourVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscFourVol_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_OscOneVol_20")
	pi = self->__commonstate.params + 9;
	pi->name = "OscOneVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscOneVol_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_OscSixVol_22")
	pi = self->__commonstate.params + 10;
	pi->name = "OscSixVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscSixVol_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_OscThreeVol_16")
	pi = self->__commonstate.params + 11;
	pi->name = "OscThreeVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscThreeVol_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_OscTwoVol_21")
	pi = self->__commonstate.params + 12;
	pi->name = "OscTwoVol";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_OscTwoVol_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_ReDux_14")
	pi = self->__commonstate.params + 13;
	pi->name = "ReDux";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ReDux_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 1.3;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_Spread_27")
	pi = self->__commonstate.params + 14;
	pi->name = "Spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Spread_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_Volume_24")
	pi = self->__commonstate.params + 15;
	pi->name = "Volume";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Volume_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // C74_GENPLUGIN::

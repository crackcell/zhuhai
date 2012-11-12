/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_MATH_H_
#define _ZH_MATH_H_

/**
 * Math utilities
 *
 * @file zh_math.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Nov 11 22:45:49 2012
 *
 **/

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////// double compare: use relative error

static const double zh_double_max_epsilon = 0.000001;

static inline int zh_compare_double(double a, double b) {
    if (a == b) {
        return 1;
    }
    return fabs(a - b) / b < zh_double_max_epsilon;
}

/////////////////////// calculate log() function by looking up table

static const int zh_log_table_length = 1025;
static const double zh_log_table[] = {
    -1.0, 0.000000, 0.693147, 1.098612, 1.386294, 1.609438, 1.791759, 1.945910, 2.079442, 2.197225,
    2.302585, 2.397895, 2.484907, 2.564949, 2.639057, 2.708050, 2.772589, 2.833213, 2.890372, 2.944439,
    2.995732, 3.044522, 3.091042, 3.135494, 3.178054, 3.218876, 3.258097, 3.295837, 3.332205, 3.367296,
    3.401197, 3.433987, 3.465736, 3.496508, 3.526361, 3.555348, 3.583519, 3.610918, 3.637586, 3.663562,
    3.688879, 3.713572, 3.737670, 3.761200, 3.784190, 3.806662, 3.828641, 3.850148, 3.871201, 3.891820,
    3.912023, 3.931826, 3.951244, 3.970292, 3.988984, 4.007333, 4.025352, 4.043051, 4.060443, 4.077537,
    4.094345, 4.110874, 4.127134, 4.143135, 4.158883, 4.174387, 4.189655, 4.204693, 4.219508, 4.234107,
    4.248495, 4.262680, 4.276666, 4.290459, 4.304065, 4.317488, 4.330733, 4.343805, 4.356709, 4.369448,
    4.382027, 4.394449, 4.406719, 4.418841, 4.430817, 4.442651, 4.454347, 4.465908, 4.477337, 4.488636,
    4.499810, 4.510860, 4.521789, 4.532599, 4.543295, 4.553877, 4.564348, 4.574711, 4.584967, 4.595120,
    4.605170, 4.615121, 4.624973, 4.634729, 4.644391, 4.653960, 4.663439, 4.672829, 4.682131, 4.691348,
    4.700480, 4.709530, 4.718499, 4.727388, 4.736198, 4.744932, 4.753590, 4.762174, 4.770685, 4.779123,
    4.787492, 4.795791, 4.804021, 4.812184, 4.820282, 4.828314, 4.836282, 4.844187, 4.852030, 4.859812,
    4.867534, 4.875197, 4.882802, 4.890349, 4.897840, 4.905275, 4.912655, 4.919981, 4.927254, 4.934474,
    4.941642, 4.948760, 4.955827, 4.962845, 4.969813, 4.976734, 4.983607, 4.990433, 4.997212, 5.003946,
    5.010635, 5.017280, 5.023881, 5.030438, 5.036953, 5.043425, 5.049856, 5.056246, 5.062595, 5.068904,
    5.075174, 5.081404, 5.087596, 5.093750, 5.099866, 5.105945, 5.111988, 5.117994, 5.123964, 5.129899,
    5.135798, 5.141664, 5.147494, 5.153292, 5.159055, 5.164786, 5.170484, 5.176150, 5.181784, 5.187386,
    5.192957, 5.198497, 5.204007, 5.209486, 5.214936, 5.220356, 5.225747, 5.231109, 5.236442, 5.241747,
    5.247024, 5.252273, 5.257495, 5.262690, 5.267858, 5.273000, 5.278115, 5.283204, 5.288267, 5.293305,
    5.298317, 5.303305, 5.308268, 5.313206, 5.318120, 5.323010, 5.327876, 5.332719, 5.337538, 5.342334,
    5.347108, 5.351858, 5.356586, 5.361292, 5.365976, 5.370638, 5.375278, 5.379897, 5.384495, 5.389072,
    5.393628, 5.398163, 5.402677, 5.407172, 5.411646, 5.416100, 5.420535, 5.424950, 5.429346, 5.433722,
    5.438079, 5.442418, 5.446737, 5.451038, 5.455321, 5.459586, 5.463832, 5.468060, 5.472271, 5.476464,
    5.480639, 5.484797, 5.488938, 5.493061, 5.497168, 5.501258, 5.505332, 5.509388, 5.513429, 5.517453,
    5.521461, 5.525453, 5.529429, 5.533389, 5.537334, 5.541264, 5.545177, 5.549076, 5.552960, 5.556828,
    5.560682, 5.564520, 5.568345, 5.572154, 5.575949, 5.579730, 5.583496, 5.587249, 5.590987, 5.594711,
    5.598422, 5.602119, 5.605802, 5.609472, 5.613128, 5.616771, 5.620401, 5.624018, 5.627621, 5.631212,
    5.634790, 5.638355, 5.641907, 5.645447, 5.648974, 5.652489, 5.655992, 5.659482, 5.662960, 5.666427,
    5.669881, 5.673323, 5.676754, 5.680173, 5.683580, 5.686975, 5.690359, 5.693732, 5.697093, 5.700444,
    5.703782, 5.707110, 5.710427, 5.713733, 5.717028, 5.720312, 5.723585, 5.726848, 5.730100, 5.733341,
    5.736572, 5.739793, 5.743003, 5.746203, 5.749393, 5.752573, 5.755742, 5.758902, 5.762051, 5.765191,
    5.768321, 5.771441, 5.774552, 5.777652, 5.780744, 5.783825, 5.786897, 5.789960, 5.793014, 5.796058,
    5.799093, 5.802118, 5.805135, 5.808142, 5.811141, 5.814131, 5.817111, 5.820083, 5.823046, 5.826000,
    5.828946, 5.831882, 5.834811, 5.837730, 5.840642, 5.843544, 5.846439, 5.849325, 5.852202, 5.855072,
    5.857933, 5.860786, 5.863631, 5.866468, 5.869297, 5.872118, 5.874931, 5.877736, 5.880533, 5.883322,
    5.886104, 5.888878, 5.891644, 5.894403, 5.897154, 5.899897, 5.902633, 5.905362, 5.908083, 5.910797,
    5.913503, 5.916202, 5.918894, 5.921578, 5.924256, 5.926926, 5.929589, 5.932245, 5.934894, 5.937536,
    5.940171, 5.942799, 5.945421, 5.948035, 5.950643, 5.953243, 5.955837, 5.958425, 5.961005, 5.963579,
    5.966147, 5.968708, 5.971262, 5.973810, 5.976351, 5.978886, 5.981414, 5.983936, 5.986452, 5.988961,
    5.991465, 5.993961, 5.996452, 5.998937, 6.001415, 6.003887, 6.006353, 6.008813, 6.011267, 6.013715,
    6.016157, 6.018593, 6.021023, 6.023448, 6.025866, 6.028279, 6.030685, 6.033086, 6.035481, 6.037871,
    6.040255, 6.042633, 6.045005, 6.047372, 6.049733, 6.052089, 6.054439, 6.056784, 6.059123, 6.061457,
    6.063785, 6.066108, 6.068426, 6.070738, 6.073045, 6.075346, 6.077642, 6.079933, 6.082219, 6.084499,
    6.086775, 6.089045, 6.091310, 6.093570, 6.095825, 6.098074, 6.100319, 6.102559, 6.104793, 6.107023,
    6.109248, 6.111467, 6.113682, 6.115892, 6.118097, 6.120297, 6.122493, 6.124683, 6.126869, 6.129050,
    6.131226, 6.133398, 6.135565, 6.137727, 6.139885, 6.142037, 6.144186, 6.146329, 6.148468, 6.150603,
    6.152733, 6.154858, 6.156979, 6.159095, 6.161207, 6.163315, 6.165418, 6.167516, 6.169611, 6.171701,
    6.173786, 6.175867, 6.177944, 6.180017, 6.182085, 6.184149, 6.186209, 6.188264, 6.190315, 6.192362,
    6.194405, 6.196444, 6.198479, 6.200509, 6.202536, 6.204558, 6.206576, 6.208590, 6.210600, 6.212606,
    6.214608, 6.216606, 6.218600, 6.220590, 6.222576, 6.224558, 6.226537, 6.228511, 6.230481, 6.232448,
    6.234411, 6.236370, 6.238325, 6.240276, 6.242223, 6.244167, 6.246107, 6.248043, 6.249975, 6.251904,
    6.253829, 6.255750, 6.257668, 6.259581, 6.261492, 6.263398, 6.265301, 6.267201, 6.269096, 6.270988,
    6.272877, 6.274762, 6.276643, 6.278521, 6.280396, 6.282267, 6.284134, 6.285998, 6.287859, 6.289716,
    6.291569, 6.293419, 6.295266, 6.297109, 6.298949, 6.300786, 6.302619, 6.304449, 6.306275, 6.308098,
    6.309918, 6.311735, 6.313548, 6.315358, 6.317165, 6.318968, 6.320768, 6.322565, 6.324359, 6.326149,
    6.327937, 6.329721, 6.331502, 6.333280, 6.335054, 6.336826, 6.338594, 6.340359, 6.342121, 6.343880,
    6.345636, 6.347389, 6.349139, 6.350886, 6.352629, 6.354370, 6.356108, 6.357842, 6.359574, 6.361302,
    6.363028, 6.364751, 6.366470, 6.368187, 6.369901, 6.371612, 6.373320, 6.375025, 6.376727, 6.378426,
    6.380123, 6.381816, 6.383507, 6.385194, 6.386879, 6.388561, 6.390241, 6.391917, 6.393591, 6.395262,
    6.396930, 6.398595, 6.400257, 6.401917, 6.403574, 6.405228, 6.406880, 6.408529, 6.410175, 6.411818,
    6.413459, 6.415097, 6.416732, 6.418365, 6.419995, 6.421622, 6.423247, 6.424869, 6.426488, 6.428105,
    6.429719, 6.431331, 6.432940, 6.434547, 6.436150, 6.437752, 6.439350, 6.440947, 6.442540, 6.444131,
    6.445720, 6.447306, 6.448889, 6.450470, 6.452049, 6.453625, 6.455199, 6.456770, 6.458338, 6.459904,
    6.461468, 6.463029, 6.464588, 6.466145, 6.467699, 6.469250, 6.470800, 6.472346, 6.473891, 6.475433,
    6.476972, 6.478510, 6.480045, 6.481577, 6.483107, 6.484635, 6.486161, 6.487684, 6.489205, 6.490724,
    6.492240, 6.493754, 6.495266, 6.496775, 6.498282, 6.499787, 6.501290, 6.502790, 6.504288, 6.505784,
    6.507278, 6.508769, 6.510258, 6.511745, 6.513230, 6.514713, 6.516193, 6.517671, 6.519147, 6.520621,
    6.522093, 6.523562, 6.525030, 6.526495, 6.527958, 6.529419, 6.530878, 6.532334, 6.533789, 6.535241,
    6.536692, 6.538140, 6.539586, 6.541030, 6.542472, 6.543912, 6.545350, 6.546785, 6.548219, 6.549651,
    6.551080, 6.552508, 6.553933, 6.555357, 6.556778, 6.558198, 6.559615, 6.561031, 6.562444, 6.563856,
    6.565265, 6.566672, 6.568078, 6.569481, 6.570883, 6.572283, 6.573680, 6.575076, 6.576470, 6.577861,
    6.579251, 6.580639, 6.582025, 6.583409, 6.584791, 6.586172, 6.587550, 6.588926, 6.590301, 6.591674,
    6.593045, 6.594413, 6.595781, 6.597146, 6.598509, 6.599870, 6.601230, 6.602588, 6.603944, 6.605298,
    6.606650, 6.608001, 6.609349, 6.610696, 6.612041, 6.613384, 6.614726, 6.616065, 6.617403, 6.618739,
    6.620073, 6.621406, 6.622736, 6.624065, 6.625392, 6.626718, 6.628041, 6.629363, 6.630683, 6.632002,
    6.633318, 6.634633, 6.635947, 6.637258, 6.638568, 6.639876, 6.641182, 6.642487, 6.643790, 6.645091,
    6.646391, 6.647688, 6.648985, 6.650279, 6.651572, 6.652863, 6.654153, 6.655440, 6.656727, 6.658011,
    6.659294, 6.660575, 6.661855, 6.663133, 6.664409, 6.665684, 6.666957, 6.668228, 6.669498, 6.670766,
    6.672033, 6.673298, 6.674561, 6.675823, 6.677083, 6.678342, 6.679599, 6.680855, 6.682109, 6.683361,
    6.684612, 6.685861, 6.687109, 6.688355, 6.689599, 6.690842, 6.692084, 6.693324, 6.694562, 6.695799,
    6.697034, 6.698268, 6.699500, 6.700731, 6.701960, 6.703188, 6.704414, 6.705639, 6.706862, 6.708084,
    6.709304, 6.710523, 6.711740, 6.712956, 6.714171, 6.715383, 6.716595, 6.717805, 6.719013, 6.720220,
    6.721426, 6.722630, 6.723832, 6.725034, 6.726233, 6.727432, 6.728629, 6.729824, 6.731018, 6.732211,
    6.733402, 6.734592, 6.735780, 6.736967, 6.738152, 6.739337, 6.740519, 6.741701, 6.742881, 6.744059,
    6.745236, 6.746412, 6.747587, 6.748760, 6.749931, 6.751101, 6.752270, 6.753438, 6.754604, 6.755769,
    6.756932, 6.758095, 6.759255, 6.760415, 6.761573, 6.762730, 6.763885, 6.765039, 6.766192, 6.767343,
    6.768493, 6.769642, 6.770789, 6.771936, 6.773080, 6.774224, 6.775366, 6.776507, 6.777647, 6.778785,
    6.779922, 6.781058, 6.782192, 6.783325, 6.784457, 6.785588, 6.786717, 6.787845, 6.788972, 6.790097,
    6.791221, 6.792344, 6.793466, 6.794587, 6.795706, 6.796824, 6.797940, 6.799056, 6.800170, 6.801283,
    6.802395, 6.803505, 6.804615, 6.805723, 6.806829, 6.807935, 6.809039, 6.810142, 6.811244, 6.812345,
    6.813445, 6.814543, 6.815640, 6.816736, 6.817831, 6.818924, 6.820016, 6.821107, 6.822197, 6.823286,
    6.824374, 6.825460, 6.826545, 6.827629, 6.828712, 6.829794, 6.830874, 6.831954, 6.833032, 6.834109,
    6.835185, 6.836259, 6.837333, 6.838405, 6.839476, 6.840547, 6.841615, 6.842683, 6.843750, 6.844815,
    6.845880, 6.846943, 6.848005, 6.849066, 6.850126, 6.851185, 6.852243, 6.853299, 6.854355, 6.855409,
    6.856462, 6.857514, 6.858565, 6.859615, 6.860664, 6.861711, 6.862758, 6.863803, 6.864848, 6.865891,
    6.866933, 6.867974, 6.869014, 6.870053, 6.871091, 6.872128, 6.873164, 6.874198, 6.875232, 6.876265,
    6.877296, 6.878326, 6.879356, 6.880384, 6.881411, 6.882437, 6.883463, 6.884487, 6.885510, 6.886532,
    6.887553, 6.888572, 6.889591, 6.890609, 6.891626, 6.892642, 6.893656, 6.894670, 6.895683, 6.896694,
    6.897705, 6.898715, 6.899723, 6.900731, 6.901737, 6.902743, 6.903747, 6.904751, 6.905753, 6.906755,
    6.907755, 6.908755, 6.909753, 6.910751, 6.911747, 6.912743, 6.913737, 6.914731, 6.915723, 6.916715,
    6.917706, 6.918695, 6.919684, 6.920672, 6.921658, 6.922644, 6.923629, 6.924612, 6.925595, 6.926577,
    6.927558, 6.928538, 6.929517, 6.930495, 6.931472
};

/**
 * Caculate log by looking up table
 *
 * @param [in] val : in value
 * @return inline double : the result
 * @see
 * @note
 * @author Tan Menglong
 * @date Sun Nov 11 23:04:29 2012
 */
static inline double zh_log_int(int val) {
    if (val < 0) {
        return -1;
    }

    const int max_lognumber = zh_log_table_length - 1;

    if (val <= max_lognumber) {
        return zh_log_table[val];
    } else {
        return log(val);
    }
}


#ifdef __cplusplus
}
#endif

#endif /* _ZH_MATH_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */

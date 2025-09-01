# MQxx-Arduino-Module
Class for MQxx sensors incluiding MQ2, MQ3,MQ4,MQ5,MQ6,MQ7,MQ8,MQ135

<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">In principle, MQ-Series Sensors have internal sensor resistor Rs and an external load resistor RL forms a voltage divider. The sensor resistor varies depending on the type of gas it measures, and its density is measured in PPM. The data sheet measures PPM vs the ration or sensor resistance (Rs) over Zero resistance (R0).</span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">Zero resistance (R0) calculated from the formula R0= Rs (in clear air) / Constant from data sheet</span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">The relation between (Rs/R0) and PPM is exponential as shown in below MQ-135 data sheet chart hence the formula to calculate the PPM should be in the form of</span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><i><span style="line-height:115%;"><strong>Log10(PPM) = A + B * Log10(Rs/R0)</strong></span></i></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:11.0pt;"><span style="line-height:115%;">or&nbsp;</span></span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><i><span style="line-height:115%;"><strong>PPM = 10 ^ (A + B * Log10(Rs/R0))</strong></span></i></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">Where A and B are constant depending on the sensor and gas type, accordingly, we should reference the charts for each sensor to extract the value of A and B from it.</span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">To calculate Rs from normal voltage divider between two resistances.</span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>Current in Sensor (V/R)<sub>S</sub> = Current output to ground (V/R)<sub>L</sub></strong></span></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">so</span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>Vs / Rs = VL / RL</strong></span></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">(Knowing that R<sub>l&nbsp;</sub>= 1K ohm for all the sensors, V<sub>l</sub>= V<sub>out</sub> from the sensor reading so)</span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>R<sub>s</sub> = Vs * R<sub>L</sub> / V<sub>out</sub> = V<sub>s</sub> / V<sub>out</sub></strong></span></span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>V<sub>s</sub> = Voltage over sensor = V<sub>cc</sub> - V<sub>out</sub></strong></span></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">In Arduino PWN pins read the voltage to 10 register bits means when the input voltage = max voltage (Vcc) then the reading will be 1023.</span>
</p>
<p style="line-height:115%;margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">So for any reading to get the corresponding voltage, we should calculate it with the following formulation.</span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>V<sub>out</sub> = Vcc * Reading / 1023</strong></span></span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;">and</span></span>
</p>
<p style="line-height:115%;margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><span style="line-height:115%;"><strong>Rs = Vs / V<sub>out</sub> = (V<sub>cc</sub> - V<sub>out</sub>) / V<sub>out</sub></strong></span></span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong><u>MQ-4 Datasheet</u></strong></span>
</p>
<p style="margin:0in;text-align:center;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span></span></span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">Calculation of the logscale&nbsp;</span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">PPM = 10 ^ ( A + B * Log10( Rs/R0 ) )</span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">According to <strong>Point1</strong> (Log10(PPM)<sub>1</sub>,Log10(Rs/R0)<sub>1</sub>), <strong>Point2</strong>(Log10(PPM)<sub>2</sub>,Log10(Rs/R0)<sub>2</sub>)</span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">Where:</span>
</p>
<p style="margin:0in;text-indent:.5in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">B = (Log10(PPM)<sub>1</sub> - Log10(PPM)<sub>2</sub>) / (Log10(Rs/R0)<sub>1</sub> - Log10(Rs/R0)<sub>2</sub>)</span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span>A = Log(PPM)<sub>1</sub> – B * Log10(Rs/R0)<sub>1</sub></span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">A and B is constants calculated depend on gas type according to above chart, hence the calculated constant show below:</span>
</p>
<div align="center">
    <figure class="table" style="width:372.05pt;">
        <table style="border-collapse:collapse;border-style:none;" border="1" cellspacing="0" cellpadding="0" width="496">
            <tbody>
                <tr style="height:27.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:none;border-top-style:solid;border-width:1.0pt;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>&nbsp;</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom:1.0pt solid white;border-left-style:none;border-right-style:none;border-top:1.0pt solid white;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><strong>PPM</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom:1.0pt solid white;border-left-style:none;border-right-style:none;border-top:1.0pt solid white;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><strong>Rs/Ro</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom:1.0pt solid white;border-left-style:none;border-right-style:none;border-top:1.0pt solid white;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><strong>LOG(PPM)&nbsp;</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom:1.0pt solid white;border-left-style:none;border-right-style:none;border-top:1.0pt solid white;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:12.0pt;"><strong>LOG(Rs/Ro)&nbsp;</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom:1.0pt solid white;border-left-style:none;border-right-style:none;border-top:1.0pt solid white;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;text-align:center;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:16.0pt;"><strong>A</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:none;border-right-style:solid;border-top-style:solid;border-width:1.0pt;height:27.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;text-align:center;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:16.0pt;"><strong>B</strong></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>LPG</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">2.56</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.4082&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>3.5410&nbsp;</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-3.6735</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">0.75</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>(0.1249)</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>CH4</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">1.71</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.2330&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.8026&nbsp;</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-3.2669</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">0.43</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>(0.3665)</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>H2</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">3.77</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.5763&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>5.6925&nbsp;</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-6.3351</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">1.85</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.2672&nbsp;</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>CO</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">4.37</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.6405&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>14.7252&nbsp;</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-19.8035</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">3.48</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.5416&nbsp;</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>Alcohol</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">4</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.6021&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>12.0550&nbsp;</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-16.6322</span>
                        </p>
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">3.05</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.4843&nbsp;</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#0F6FC6;border-bottom-style:solid;border-color:white;border-left-style:solid;border-right-style:solid;border-top-style:none;border-width:1.0pt;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64">
                        <p style="margin:0in;">
                            <span style="color:white;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><strong>Smoke</strong></span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">110</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">3.77</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>2.0414&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.5763&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>7.7442&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#90C5F6;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" rowspan="2" width="64">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">-9.8948</span>
                        </p>
                    </td>
                </tr>
                <tr style="height:15.0pt;">
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">10000</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:48.0pt;" width="64" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;">2.39</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:63.0pt;" width="84" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>4.0000&nbsp;</span>
                        </p>
                    </td>
                    <td style="background-color:#C7E2FA;border-bottom:1.0pt solid white;border-left-style:none;border-right:1.0pt solid white;border-top-style:none;height:15.0pt;padding:0in 5.4pt;vertical-align:top;width:69.05pt;" width="92" nowrap="">
                        <p style="margin:0in;">
                            <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"><span>&nbsp;</span>0.3784&nbsp;</span>
                        </p>
                    </td>
                </tr>
            </tbody>
        </table>
    </figure>
</div>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:11.0pt;">Rs/R0 in clear air = 4.434</span>
</p>
<p style="margin:0in;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:11.0pt;">Accordingly, R0 = Calibrated Rs (initial value) / 4.434</span>
</p>
<div class="page-break" style="page-break-after:always;">
    <span style="display:none;">&nbsp;</span>
</div>
<p style="line-height:115%;margin:0in 0in 10.0pt;">
    <span style="color:black;font-family:&quot;Calibri&quot;, sans-serif;font-size:10pt;"></span>
</p>

#I @"e:\ProjectGit\FsharpMyExtension\FsharpMyExtension\FsharpMyExtension\bin\Release\net461\"
#r @"FParsecCS.dll"
#r @"FParsec.dll"
#r @"Fuchu.dll"
#r @"HtmlAgilityPack.dll"
#r @"Newtonsoft.Json.dll"
#r @"Newtonsoft.Json.Bson.dll"
#r @"FsharpMyExtension.dll"

open FsharpMyExtension

let r = System.Random()
let genRandoms a b length =
    List.init length (fun _ ->
        r.NextDouble() * (b - a) + a
    )

// let randoms = genRandoms 0.3 0.75 10

let buildHistogramRanges (histMin, histMax) histLines randoms =
    let diff = (histMax - histMin) / float histLines

    Seq.unfold (fun x -> Some ((x, x + diff), x + diff)) histMin
    |> Seq.take 5
    |> List.ofSeq


let buildHistogram (histMin, histMax) histLines randoms =
    // let histMin, histMax = 0.2, 1.0
    // let histLines = 5

    let diff = (histMax - histMin) / float histLines


    let counts = Array.create histLines 0

    for i = 0 to histLines - 1 do
        let min = histMin + (float i * diff)
        let max = histMin + (float (i + 1) * diff)

        for random in randoms do
            if min <= random && random < max then
                counts.[i] <- counts.[i] + 1

    counts

open Fuchu

[<Tests>]
let buildHistogramTests =
    // let testDoubleLists exp act =
    //     let accuracy = 0.01
    //     List.forall2
    //         (fun (x, y) (x', y') -> abs(x - x') < accuracy && abs(y - y') < accuracy)
    //         exp
    //         act

    testList "buildHistogramTests" [
        testCase "1" <| fun _ ->
            let input =
                [0.0; 0.0; 0.0; 0.0; 1.0; 1.0; 1.0; 2.0; 4.0; 4.0; 5.0; 5.0; 6.0; 6.0; 6.0; 8.0; 9.0; 9.0; 9.0; 9.0]

            let histMin, histMax = 0.1, 8.0
            let histLines = 5

            let exp =
                [(0.1, 1.6800000000000002); (1.6800000000000002, 3.2600000000000002);
                 (3.2600000000000002, 4.84); (4.84, 6.42); (6.42, 8.0)]
            let act = buildHistogramRanges (histMin, histMax) histLines input
            Assert.Equal("", exp, act)

            let exp = [|3; 1; 2; 5; 0|]
            let act = buildHistogram (histMin, histMax) histLines input
            Assert.Equal("", exp, act)

        testCase "2" <| fun _ ->
            let input =
                [0.310643; 0.341145; 0.34153; 0.400679; 0.429011; 0.518401; 0.531874; 0.592177; 0.609632; 0.651312]

            let histMin, histMax = 0.0, 1.0
            let histLines = 5

            let exp =
                [(0.0, 0.2); (0.2, 0.4); (0.4, 0.6000000000000001);
                 (0.6000000000000001, 0.8); (0.8, 1.0)]
            let act = buildHistogramRanges (histMin, histMax) histLines input
            Assert.Equal("", exp, act)

            let exp = [|0; 3; 5; 2; 0|]
            let act = buildHistogram (histMin, histMax) histLines input
            Assert.Equal("", exp, act)
    ]

// run buildHistogramTests

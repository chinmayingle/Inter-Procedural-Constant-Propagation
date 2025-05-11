; ModuleID = 'file2.c'
source_filename = "file2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @compute(i32 noundef %a, i32 noundef %b) #0 !dbg !17 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !22, metadata !DIExpression()), !dbg !23
  store i32 %b, ptr %b.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %b.addr, metadata !24, metadata !DIExpression()), !dbg !25
  %0 = load i32, ptr %a.addr, align 4, !dbg !26
  %1 = load i32, ptr %b.addr, align 4, !dbg !27
  %div = sdiv i32 %0, %1, !dbg !28
  store i32 %div, ptr %a.addr, align 4, !dbg !29
  ret void, !dbg !30
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !31 {
entry:
  %retval = alloca i32, align 4
  %l = alloca i32, align 4
  %m = alloca i32, align 4
  %flag = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  tail call void @llvm.dbg.declare(metadata ptr %l, metadata !34, metadata !DIExpression()), !dbg !35
  store i32 40, ptr %l, align 4, !dbg !35
  tail call void @llvm.dbg.declare(metadata ptr %m, metadata !36, metadata !DIExpression()), !dbg !37
  store i32 89, ptr %m, align 4, !dbg !37
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %l), !dbg !38
  tail call void @llvm.dbg.declare(metadata ptr %flag, metadata !39, metadata !DIExpression()), !dbg !40
  %0 = load i32, ptr %l, align 4, !dbg !41
  %cmp = icmp sgt i32 %0, 0, !dbg !42
  %1 = zext i1 %cmp to i64, !dbg !41
  %cond = select i1 %cmp, i32 1, i32 0, !dbg !41
  store i32 %cond, ptr %flag, align 4, !dbg !40
  %2 = load i32, ptr %flag, align 4, !dbg !43
  %tobool = icmp ne i32 %2, 0, !dbg !43
  br i1 %tobool, label %if.then, label %if.else, !dbg !45

if.then:                                          ; preds = %entry
  %3 = load i32, ptr %l, align 4, !dbg !46
  %4 = load i32, ptr %m, align 4, !dbg !48
  call void @compute(i32 noundef %3, i32 noundef %4), !dbg !49
  br label %if.end, !dbg !50

if.else:                                          ; preds = %entry
  call void @compute(i32 noundef 40, i32 noundef 89), !dbg !51
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = load i32, ptr %retval, align 4, !dbg !53
  ret i32 %5, !dbg !53
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "file2.c", directory: "/home/soumik/Documents/assignment-4(public)", checksumkind: CSK_MD5, checksum: "e8e0fea17f55266641798b354afed21f")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 24, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 3)
!7 = distinct !DICompileUnit(language: DW_LANG_C11, file: !2, producer: "clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !8, splitDebugInlining: false, nameTableKind: None)
!8 = !{!0}
!9 = !{i32 7, !"Dwarf Version", i32 5}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{i32 8, !"PIC Level", i32 2}
!13 = !{i32 7, !"PIE Level", i32 2}
!14 = !{i32 7, !"uwtable", i32 2}
!15 = !{i32 7, !"frame-pointer", i32 2}
!16 = !{!"clang version 19.0.0git (https://github.com/llvm/llvm-project.git 13078cbc3eeb0ae91c370ce0f604f7165b26e0c8)"}
!17 = distinct !DISubprogram(name: "compute", scope: !2, file: !2, line: 2, type: !18, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!18 = !DISubroutineType(types: !19)
!19 = !{null, !20, !20}
!20 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!21 = !{}
!22 = !DILocalVariable(name: "a", arg: 1, scope: !17, file: !2, line: 2, type: !20)
!23 = !DILocation(line: 2, column: 18, scope: !17)
!24 = !DILocalVariable(name: "b", arg: 2, scope: !17, file: !2, line: 2, type: !20)
!25 = !DILocation(line: 2, column: 25, scope: !17)
!26 = !DILocation(line: 3, column: 6, scope: !17)
!27 = !DILocation(line: 3, column: 10, scope: !17)
!28 = !DILocation(line: 3, column: 8, scope: !17)
!29 = !DILocation(line: 3, column: 4, scope: !17)
!30 = !DILocation(line: 4, column: 1, scope: !17)
!31 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 6, type: !32, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!32 = !DISubroutineType(types: !33)
!33 = !{!20}
!34 = !DILocalVariable(name: "l", scope: !31, file: !2, line: 8, type: !20)
!35 = !DILocation(line: 8, column: 6, scope: !31)
!36 = !DILocalVariable(name: "m", scope: !31, file: !2, line: 9, type: !20)
!37 = !DILocation(line: 9, column: 6, scope: !31)
!38 = !DILocation(line: 10, column: 2, scope: !31)
!39 = !DILocalVariable(name: "flag", scope: !31, file: !2, line: 11, type: !20)
!40 = !DILocation(line: 11, column: 6, scope: !31)
!41 = !DILocation(line: 11, column: 13, scope: !31)
!42 = !DILocation(line: 11, column: 14, scope: !31)
!43 = !DILocation(line: 12, column: 5, scope: !44)
!44 = distinct !DILexicalBlock(scope: !31, file: !2, line: 12, column: 5)
!45 = !DILocation(line: 12, column: 5, scope: !31)
!46 = !DILocation(line: 14, column: 11, scope: !47)
!47 = distinct !DILexicalBlock(scope: !44, file: !2, line: 13, column: 2)
!48 = !DILocation(line: 14, column: 13, scope: !47)
!49 = !DILocation(line: 14, column: 3, scope: !47)
!50 = !DILocation(line: 15, column: 2, scope: !47)
!51 = !DILocation(line: 18, column: 3, scope: !52)
!52 = distinct !DILexicalBlock(scope: !44, file: !2, line: 17, column: 2)
!53 = !DILocation(line: 20, column: 1, scope: !31)

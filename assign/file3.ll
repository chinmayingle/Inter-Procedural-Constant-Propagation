; ModuleID = 'file3.c'
source_filename = "file3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @funx(i32 noundef %x, i32 noundef %y) #0 !dbg !17 {
entry:
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  store i32 %x, ptr %x.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x.addr, metadata !22, metadata !DIExpression()), !dbg !23
  store i32 %y, ptr %y.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %y.addr, metadata !24, metadata !DIExpression()), !dbg !25
  %0 = load i32, ptr %y.addr, align 4, !dbg !26
  %mul = mul nsw i32 %0, 90, !dbg !27
  store i32 %mul, ptr %x.addr, align 4, !dbg !28
  %1 = load i32, ptr %x.addr, align 4, !dbg !29
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %1), !dbg !30
  ret void, !dbg !31
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(ptr noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @barx(i32 noundef %x, i32 noundef %y) #0 !dbg !32 {
entry:
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  store i32 %x, ptr %x.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x.addr, metadata !33, metadata !DIExpression()), !dbg !34
  store i32 %y, ptr %y.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %y.addr, metadata !35, metadata !DIExpression()), !dbg !36
  %0 = load i32, ptr %y.addr, align 4, !dbg !37
  %add = add nsw i32 %0, 89, !dbg !38
  store i32 %add, ptr %x.addr, align 4, !dbg !39
  %1 = load i32, ptr %x.addr, align 4, !dbg !40
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %1), !dbg !41
  ret void, !dbg !42
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foox(i32 noundef %x, i32 noundef %y, i32 noundef %z, i32 noundef %w) #0 !dbg !43 {
entry:
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  %z.addr = alloca i32, align 4
  %w.addr = alloca i32, align 4
  %flag = alloca i32, align 4
  store i32 %x, ptr %x.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x.addr, metadata !46, metadata !DIExpression()), !dbg !47
  store i32 %y, ptr %y.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %y.addr, metadata !48, metadata !DIExpression()), !dbg !49
  store i32 %z, ptr %z.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %z.addr, metadata !50, metadata !DIExpression()), !dbg !51
  store i32 %w, ptr %w.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %w.addr, metadata !52, metadata !DIExpression()), !dbg !53
  tail call void @llvm.dbg.declare(metadata ptr %flag, metadata !54, metadata !DIExpression()), !dbg !55
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %flag), !dbg !56
  %0 = load i32, ptr %flag, align 4, !dbg !57
  %1 = load i32, ptr %y.addr, align 4, !dbg !58
  %add = add nsw i32 %0, %1, !dbg !59
  store i32 %add, ptr %flag, align 4, !dbg !60
  %2 = load i32, ptr %flag, align 4, !dbg !61
  %cmp = icmp sgt i32 %2, 0, !dbg !63
  br i1 %cmp, label %if.then, label %if.end, !dbg !64

if.then:                                          ; preds = %entry
  %3 = load i32, ptr %x.addr, align 4, !dbg !65
  %4 = load i32, ptr %y.addr, align 4, !dbg !67
  %add1 = add nsw i32 %3, %4, !dbg !68
  store i32 %add1, ptr %z.addr, align 4, !dbg !69
  store i32 0, ptr %w.addr, align 4, !dbg !70
  br label %if.end, !dbg !71

if.end:                                           ; preds = %if.then, %entry
  %5 = load i32, ptr %z.addr, align 4, !dbg !72
  %6 = load i32, ptr %w.addr, align 4, !dbg !73
  call void @funx(i32 noundef %5, i32 noundef %6), !dbg !74
  %7 = load i32, ptr %w.addr, align 4, !dbg !75
  %8 = load i32, ptr %z.addr, align 4, !dbg !76
  call void @barx(i32 noundef %7, i32 noundef %8), !dbg !77
  ret void, !dbg !78
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !79 {
entry:
  %x = alloca i32, align 4
  tail call void @llvm.dbg.declare(metadata ptr %x, metadata !82, metadata !DIExpression()), !dbg !83
  store i32 5, ptr %x, align 4, !dbg !83
  %0 = load i32, ptr %x, align 4, !dbg !84
  call void @foox(i32 noundef %0, i32 noundef 8, i32 noundef 9, i32 noundef 0), !dbg !85
  ret i32 0, !dbg !86
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 6, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "file3.c", directory: "/home/soumik/Documents/assignment-4(public)", checksumkind: CSK_MD5, checksum: "caeb006c2769454bcc9d9e43e2f4b55c")
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
!17 = distinct !DISubprogram(name: "funx", scope: !2, file: !2, line: 3, type: !18, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!18 = !DISubroutineType(types: !19)
!19 = !{null, !20, !20}
!20 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!21 = !{}
!22 = !DILocalVariable(name: "x", arg: 1, scope: !17, file: !2, line: 3, type: !20)
!23 = !DILocation(line: 3, column: 15, scope: !17)
!24 = !DILocalVariable(name: "y", arg: 2, scope: !17, file: !2, line: 3, type: !20)
!25 = !DILocation(line: 3, column: 22, scope: !17)
!26 = !DILocation(line: 5, column: 6, scope: !17)
!27 = !DILocation(line: 5, column: 8, scope: !17)
!28 = !DILocation(line: 5, column: 4, scope: !17)
!29 = !DILocation(line: 6, column: 15, scope: !17)
!30 = !DILocation(line: 6, column: 2, scope: !17)
!31 = !DILocation(line: 8, column: 1, scope: !17)
!32 = distinct !DISubprogram(name: "barx", scope: !2, file: !2, line: 9, type: !18, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!33 = !DILocalVariable(name: "x", arg: 1, scope: !32, file: !2, line: 9, type: !20)
!34 = !DILocation(line: 9, column: 15, scope: !32)
!35 = !DILocalVariable(name: "y", arg: 2, scope: !32, file: !2, line: 9, type: !20)
!36 = !DILocation(line: 9, column: 22, scope: !32)
!37 = !DILocation(line: 11, column: 6, scope: !32)
!38 = !DILocation(line: 11, column: 8, scope: !32)
!39 = !DILocation(line: 11, column: 4, scope: !32)
!40 = !DILocation(line: 12, column: 15, scope: !32)
!41 = !DILocation(line: 12, column: 2, scope: !32)
!42 = !DILocation(line: 13, column: 1, scope: !32)
!43 = distinct !DISubprogram(name: "foox", scope: !2, file: !2, line: 14, type: !44, scopeLine: 15, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!44 = !DISubroutineType(types: !45)
!45 = !{null, !20, !20, !20, !20}
!46 = !DILocalVariable(name: "x", arg: 1, scope: !43, file: !2, line: 14, type: !20)
!47 = !DILocation(line: 14, column: 15, scope: !43)
!48 = !DILocalVariable(name: "y", arg: 2, scope: !43, file: !2, line: 14, type: !20)
!49 = !DILocation(line: 14, column: 22, scope: !43)
!50 = !DILocalVariable(name: "z", arg: 3, scope: !43, file: !2, line: 14, type: !20)
!51 = !DILocation(line: 14, column: 29, scope: !43)
!52 = !DILocalVariable(name: "w", arg: 4, scope: !43, file: !2, line: 14, type: !20)
!53 = !DILocation(line: 14, column: 36, scope: !43)
!54 = !DILocalVariable(name: "flag", scope: !43, file: !2, line: 16, type: !20)
!55 = !DILocation(line: 16, column: 6, scope: !43)
!56 = !DILocation(line: 17, column: 2, scope: !43)
!57 = !DILocation(line: 18, column: 8, scope: !43)
!58 = !DILocation(line: 18, column: 15, scope: !43)
!59 = !DILocation(line: 18, column: 13, scope: !43)
!60 = !DILocation(line: 18, column: 7, scope: !43)
!61 = !DILocation(line: 19, column: 5, scope: !62)
!62 = distinct !DILexicalBlock(scope: !43, file: !2, line: 19, column: 5)
!63 = !DILocation(line: 19, column: 9, scope: !62)
!64 = !DILocation(line: 19, column: 5, scope: !43)
!65 = !DILocation(line: 21, column: 7, scope: !66)
!66 = distinct !DILexicalBlock(scope: !62, file: !2, line: 20, column: 2)
!67 = !DILocation(line: 21, column: 9, scope: !66)
!68 = !DILocation(line: 21, column: 8, scope: !66)
!69 = !DILocation(line: 21, column: 5, scope: !66)
!70 = !DILocation(line: 22, column: 5, scope: !66)
!71 = !DILocation(line: 23, column: 2, scope: !66)
!72 = !DILocation(line: 24, column: 7, scope: !43)
!73 = !DILocation(line: 24, column: 9, scope: !43)
!74 = !DILocation(line: 24, column: 2, scope: !43)
!75 = !DILocation(line: 25, column: 7, scope: !43)
!76 = !DILocation(line: 25, column: 9, scope: !43)
!77 = !DILocation(line: 25, column: 2, scope: !43)
!78 = !DILocation(line: 27, column: 1, scope: !43)
!79 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 28, type: !80, scopeLine: 29, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!80 = !DISubroutineType(types: !81)
!81 = !{!20}
!82 = !DILocalVariable(name: "x", scope: !79, file: !2, line: 30, type: !20)
!83 = !DILocation(line: 30, column: 6, scope: !79)
!84 = !DILocation(line: 31, column: 7, scope: !79)
!85 = !DILocation(line: 31, column: 2, scope: !79)
!86 = !DILocation(line: 32, column: 1, scope: !79)

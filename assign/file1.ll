; ModuleID = 'file1.c'
source_filename = "file1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @add(i32 noundef %a, i32 noundef %b) #0 !dbg !17 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %global_var = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !22, metadata !DIExpression()), !dbg !23
  store i32 %b, ptr %b.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %b.addr, metadata !24, metadata !DIExpression()), !dbg !25
  tail call void @llvm.dbg.declare(metadata ptr %global_var, metadata !26, metadata !DIExpression()), !dbg !27
  %0 = load i32, ptr %a.addr, align 4, !dbg !28
  %1 = load i32, ptr %b.addr, align 4, !dbg !29
  %add = add nsw i32 %0, %1, !dbg !30
  store i32 %add, ptr %global_var, align 4, !dbg !27
  %2 = load i32, ptr %global_var, align 4, !dbg !31
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %2), !dbg !32
  ret void, !dbg !33
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(ptr noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @multiply(i32 noundef %a, i32 noundef %b) #0 !dbg !34 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %a.addr, metadata !35, metadata !DIExpression()), !dbg !36
  store i32 %b, ptr %b.addr, align 4
  tail call void @llvm.dbg.declare(metadata ptr %b.addr, metadata !37, metadata !DIExpression()), !dbg !38
  tail call void @llvm.dbg.declare(metadata ptr %c, metadata !39, metadata !DIExpression()), !dbg !40
  store i32 3, ptr %c, align 4, !dbg !40
  tail call void @llvm.dbg.declare(metadata ptr %d, metadata !41, metadata !DIExpression()), !dbg !42
  store i32 4, ptr %d, align 4, !dbg !42
  %0 = load i32, ptr %a.addr, align 4, !dbg !43
  %1 = load i32, ptr %c, align 4, !dbg !44
  %mul = mul nsw i32 %0, %1, !dbg !45
  %2 = load i32, ptr %b.addr, align 4, !dbg !46
  %3 = load i32, ptr %d, align 4, !dbg !47
  %mul1 = mul nsw i32 %2, %3, !dbg !48
  call void @add(i32 noundef %mul, i32 noundef %mul1), !dbg !49
  ret void, !dbg !50
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !51 {
entry:
  %l = alloca i32, align 4
  %m = alloca i32, align 4
  tail call void @llvm.dbg.declare(metadata ptr %l, metadata !54, metadata !DIExpression()), !dbg !55
  store i32 40, ptr %l, align 4, !dbg !55
  tail call void @llvm.dbg.declare(metadata ptr %m, metadata !56, metadata !DIExpression()), !dbg !57
  store i32 89, ptr %m, align 4, !dbg !57
  %0 = load i32, ptr %l, align 4, !dbg !58
  %1 = load i32, ptr %m, align 4, !dbg !59
  call void @multiply(i32 noundef %0, i32 noundef %1), !dbg !60
  ret i32 0, !dbg !61
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 4, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "file1.c", directory: "/home/soumik/Documents/assignment-4(public)", checksumkind: CSK_MD5, checksum: "32f0f5eeff8741bd7aafb08496e9ec04")
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
!17 = distinct !DISubprogram(name: "add", scope: !2, file: !2, line: 2, type: !18, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!18 = !DISubroutineType(types: !19)
!19 = !{null, !20, !20}
!20 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!21 = !{}
!22 = !DILocalVariable(name: "a", arg: 1, scope: !17, file: !2, line: 2, type: !20)
!23 = !DILocation(line: 2, column: 14, scope: !17)
!24 = !DILocalVariable(name: "b", arg: 2, scope: !17, file: !2, line: 2, type: !20)
!25 = !DILocation(line: 2, column: 21, scope: !17)
!26 = !DILocalVariable(name: "global_var", scope: !17, file: !2, line: 3, type: !20)
!27 = !DILocation(line: 3, column: 9, scope: !17)
!28 = !DILocation(line: 3, column: 22, scope: !17)
!29 = !DILocation(line: 3, column: 26, scope: !17)
!30 = !DILocation(line: 3, column: 24, scope: !17)
!31 = !DILocation(line: 4, column: 18, scope: !17)
!32 = !DILocation(line: 4, column: 5, scope: !17)
!33 = !DILocation(line: 5, column: 1, scope: !17)
!34 = distinct !DISubprogram(name: "multiply", scope: !2, file: !2, line: 7, type: !18, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!35 = !DILocalVariable(name: "a", arg: 1, scope: !34, file: !2, line: 7, type: !20)
!36 = !DILocation(line: 7, column: 19, scope: !34)
!37 = !DILocalVariable(name: "b", arg: 2, scope: !34, file: !2, line: 7, type: !20)
!38 = !DILocation(line: 7, column: 26, scope: !34)
!39 = !DILocalVariable(name: "c", scope: !34, file: !2, line: 8, type: !20)
!40 = !DILocation(line: 8, column: 9, scope: !34)
!41 = !DILocalVariable(name: "d", scope: !34, file: !2, line: 9, type: !20)
!42 = !DILocation(line: 9, column: 9, scope: !34)
!43 = !DILocation(line: 10, column: 9, scope: !34)
!44 = !DILocation(line: 10, column: 13, scope: !34)
!45 = !DILocation(line: 10, column: 11, scope: !34)
!46 = !DILocation(line: 10, column: 16, scope: !34)
!47 = !DILocation(line: 10, column: 20, scope: !34)
!48 = !DILocation(line: 10, column: 18, scope: !34)
!49 = !DILocation(line: 10, column: 5, scope: !34)
!50 = !DILocation(line: 11, column: 1, scope: !34)
!51 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 13, type: !52, scopeLine: 14, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !21)
!52 = !DISubroutineType(types: !53)
!53 = !{!20}
!54 = !DILocalVariable(name: "l", scope: !51, file: !2, line: 15, type: !20)
!55 = !DILocation(line: 15, column: 6, scope: !51)
!56 = !DILocalVariable(name: "m", scope: !51, file: !2, line: 16, type: !20)
!57 = !DILocation(line: 16, column: 6, scope: !51)
!58 = !DILocation(line: 17, column: 11, scope: !51)
!59 = !DILocation(line: 17, column: 13, scope: !51)
!60 = !DILocation(line: 17, column: 2, scope: !51)
!61 = !DILocation(line: 18, column: 1, scope: !51)
